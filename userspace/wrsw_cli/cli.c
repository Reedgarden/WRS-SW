/*
 * White Rabbit Switch CLI (Command Line Interface)
 * Copyright (C) 2011, CERN.
 *
 * Authors:     Miguel Baizan   (miguel.baizan@integrasys.es)
 *
 * Description: Basic CLI implementation.
 *              Initialization of data structures.
 *              Main loop.
 *              Command parsing and command line editing capabilities.
 *
 *
 *              Part of the code written here is based on ideas taken from the
 *              LGPL libcli package (https://github.com/dparrish/libcli.git)
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <readline.h>
#include <history.h>

#include "cli.h"
#include "cli_commands.h"
#include "cli_snmp.h"


/* Internal functions */
static void usage(char *name);
static int parse_string(char *string, char *commands[]);
static void free_cmds_string(int num_cmds, char *commands[]);
static char **completion(char *text, int start, int end);


static void usage(char *name)
{
    fprintf(stderr,
        "Usage: %s [-h] -p <password> -u <username>\n"
        "\t-h   help\n"
        "\t-p   The password for the SNMPv3 authentication\n"
        "\t-u   The username for the SNMPv3 authentication\n",
        name);
    exit(1);
}


/**
 * \brief Turns the string introduced by the user into an array of commands.
 * It alternatively detects white spaces and words. Each word is stored in one
 * of the elements of the commands array.
 * @param string string introduced by the user.
 * @param commands array to store the detected commands.
 * @return number of commands detected.
 */
static int parse_string(char *string, char *commands[])
{
    char *word = string;
    int num_cmds = 0;
    int i = 0;
    int cmd_length = 0;
    char *cmd_start;

    for (i = 0; i < MAX_CMDS_IN_LINE; i++) {
        while (*word && isspace(*word)) { /* Detect white spaces */
            word++;
        }

        if (!*word)
            break;

        cmd_start = word;

        while (*word && !isspace(*word)) { /* Detect words */
            word++;
            cmd_length++;
        }

        /* Allocate memory for the command */
        commands[i] = (char*)malloc(cmd_length + 1);
        if (!commands[i]) {
            return -1;
        }

        /* Copy the detected command to the array */
        memcpy(commands[i], cmd_start, cmd_length);
        commands[i][cmd_length] = 0;
        num_cmds = i + 1;

        /* Clean for the next loop */
        cmd_length = 0;

        /* Be sure that we are not yet at the end of the string */
        if (!*word)
            break;
    }

    return num_cmds;
}

/**
 * \brief It frees the temporal commands array.
 * @param num_cmds The number of elements of the array.
 * @param commands array where the detected commands are stored.
 */
static void free_cmds_string(int num_cmds, char *commands[])
{
    int i = 0;

    for (i = 0; i < num_cmds; i++)
        free(commands[i]);
}


/**
 * \brief Generator function for command completion.
 * @param cli CLI interpreter.
 * @param text the word to compete.
 * @param state lets us know whether to start from scratch; without any state
 * (i.e. STATE == 0), then we start at the top of the list.
*/
static char *command_generator(const char *text, int state)
{
    /* TODO */

    return ((char*)NULL);
}


/**
 * \brief Attempt to complete on the contents of TEXT.
 * @param text the word to compete.
 * @param start
 * @param end START and END bound the region of rl_line_buffer that contains
 * the word to complete. We can use the entire contents of rl_line_buffer
 * in case we want to do some simple parsing. Return the array of matches,
 * or NULL if there aren't any.
*/
static char **completion(char *text, int start, int end)
{
    char **matches;

    matches = (char **)NULL;

    matches = rl_completion_matches(text, command_generator);

    return matches;
}


/**
 * \brief Initialization function.
 * It allocates memory for the CLI interpreter structure and builds the commands
 * tree.
 * @return pointer to the new created CLI interpreter structure. If NULL,
 * something is wrong and the program must be exited.
 */
struct cli_shell *cli_init(void)
{
    struct cli_shell *cli;

    cli = (struct cli_shell *)malloc(sizeof(struct cli_shell));
    if (!cli)
        return NULL;

    /* Clear structure */
    memset(cli, 0, sizeof(struct cli_shell));

    /* Build the comands tree */
    cli_build_commands_tree(cli);

    /* Initialize the readline completer to our own function */
    rl_attempted_completion_function = (rl_completion_func_t *)completion;

    /* Do not attempt filename completion. We don't want that the default
       filename generator function be called when no matches are found. */
    rl_completion_entry_function = (rl_compentry_func_t *) completion;

    return cli;
}


/**
 * \brief Builds the prompt of the CLI.
 * The prompt consists of the configurable hostname of the switch followed by a
 * string representing the prompt itself.
 * @param cli CLI interpreter.
 */
void cli_build_prompt(struct cli_shell *cli)
{
    char buf[64];

    if (!cli->hostname)
        cli->hostname = strdup(DEFAULT_HOSTNAME);

    if (cli->prompt)
        free(cli->prompt);

    strcpy(&buf[0], cli->hostname);
    strcat(&buf[0], EXEC_PROMPT);
    cli->prompt = strdup(&buf[0]);
}


/**
 * \brief Find commands in the commads tree.
 * @param cli CLI interpreter.
 * @param top_cmd the command from which the search begins.
 * @param cmd command name to search.
 * @return pointer to the command found. NULL if the command is not found.
 */
struct cli_cmd *cli_find_command(
    struct cli_shell *cli, struct cli_cmd *top_cmd, char *cmd)
{
    struct cli_cmd *c;

    for (c = top_cmd; c; c = c->next) {
        if (!strcmp(c->name, cmd))
            return c; /* Command found */
    }

    return NULL;
}


/**
 * \brief Runs the command string typed by the user.
 * It first parses the command line to detect the words in the string. Then it
 * looks in the commands tree for commnads matching the words, and finally it
 * tries to execute the command. It also detects the help (or ?) command.
 * @param cli CLI interpreter.
 * @param string string typed by the user.
 */
void cli_run_command(struct cli_shell *cli, char *string)
{
    char *commands[MAX_CMDS_IN_LINE] = {0};
    int num_cmds = 0;
    struct cli_cmd *cmd = NULL;
    struct cli_cmd *c_found = NULL;
    char *h = "help";
    char *q = "?";
    int i = 0;
    int argc = 0;
    char *argv[] = {0};


    if (!string)
        return;

    /* Parse command. The commands will be stored in the 'commands' array */
    num_cmds = parse_string(string, commands);

    /* Check for allocation erors */
    if (num_cmds < 0) {
        cli->error = CLI_ALLOC_ERROR;
        return;
    }

    /* Find the commands in the commands array, and evaluate them if possible */
    for (i = 0; i < num_cmds; i++) {
        if (!cmd) {
            /* Start the search from root_cmd */
            c_found = cli_find_command(cli, cli->root_cmd, commands[i]);
        } else {
            /* Search among the children */
            c_found = cli_find_command(cli, cmd->child, commands[i]);
        }

        /* If a matching command has not been found, maybe the user has asked
           for help or we have an argument for this command */
        if (!c_found) {
            if (!strcmp(commands[i], h) || !strcmp(commands[i], q)) {
                cli_cmd_help(cli, cmd);
                free_cmds_string(num_cmds, commands);
                return;
            } else {
                if (!cmd) {
                    printf("Error. Command %s not found.\n", commands[i]);
                    return;
                } else {
                    if (!cmd->opt) {
                        printf("Error. Command %s not found.\n", commands[i]);
                        return;
                    } else {
                        /* It can be an argument. The handler will check
                           wether this is a valid argument or not */
                        argc++;
                        argv[(argc-1)] = commands[i];
                        continue;
                    }
                }
            }
        }

        /* If a previous command has been detected, check that it is the parent
           command */
        if (cmd) {
            /* But first be sure that the command found does have a parent */
            if (c_found->parent) {
                if (memcmp(cmd, c_found->parent, sizeof(struct cli_cmd))) {
                    printf("Error. Wrong command syntax.\n");
                    free_cmds_string(num_cmds, commands);
                    return;
                }
            } else {
                printf("Error. Wrong command syntax.\n");
                free_cmds_string(num_cmds, commands);
                return;
            }
        }

        cmd = c_found;
    }

    /* Run the handler associated to the last command detected */
    if (cmd) {
        if (cmd->handler) {
            cmd->handler(cli, argc, argv);
        } else {
            printf("Nothing to do for this command. Type '");
            for (i = 0; i < num_cmds; i++)
                printf("%s ", commands[i]);
            printf("help' for usage.\n");
        }
    }

    free_cmds_string(num_cmds, commands);
}


/**
 * \brief Error handling.
 * It handles the fatal errors, i.e. those errors that force the program to
 * exit. It uses the cli_cmd_exit function to de-allocate data structures.
 * @param cli CLI interpreter.
 */
void cli_print_error(struct cli_shell *cli)
{
    switch (cli->error) {
    case CLI_ALLOC_ERROR:
        fprintf(stderr, "Memory allocation error");
        break;
    case CLI_SNMP_INIT_ERROR:
        fprintf(stderr, "SNMP initialization error");
        break;
    case CLI_ERROR:
    default:
        fprintf(stderr, "Fatal generic error");
        break;
    }

    cli_cmd_exit(cli, 0, NULL);
}


/**
 * \brief Main loop.
 * Waits for the user to write a command, and then tries to run it.
 */
void cli_main_loop(struct cli_shell *cli)
{
    char *line = NULL;
    char *string;

    /* Init loop */
    while (1) {
        /* Clear the buffer. Remember that the readline function makes the
           allocation of the string internally */
        if (line) {
            free(line);
            line = NULL;
        }

        /* Use readline function to let Command Line Editing */
        line = readline(cli->prompt);

        string = line;
        while (*string && isspace(*string)) { /* Remove initial white spaces */
            string++;
        }

        /* Evaluate the commands line inserted by the user and try to run
           the command */
        cli_run_command(cli, string);

        /* If it is not an empty string, save the string to the history */
        if (string && *string)
            add_history(string);

        if (cli->error < 0)
            break;
    }

    free(string);
}


/**
 * \brief Main function.
 */
int main(int argc, char **argv)
{
    int op;
    char *s, *name, *optstring;
    char *version = VERSION;
    char *username = NULL;
    char *password = NULL;
    struct cli_shell *cli;


    /* Strip out path from argv[0] if exists, and extract command name */
    for (name = s = argv[0]; s[0]; s++) {
        if (s[0] == '/' && s[1]) {
            name = &s[1];
        }
    }

    /* Capture options */
    if (argc > 0) {
        /* Parse options */
        optstring = "hp:u:";
        while ((op = getopt(argc, argv, optstring)) != -1) {
            switch(op) {
            case 'h':
                usage(name);
                break;
            case 'p':
                password = optarg;
                break;
            case 'u':
                username = optarg;
                break;
            default:
                usage(name);
                break;
            }
        }
    }

    if (!username && !password)
        usage(name);

    /* Initialize the CLI */
    cli = cli_init();

    /* Check for initialization errors */
    if (!cli) {
        printf("Failed to allocate memory for the CLI\n");
        return CLI_ALLOC_ERROR;
    }

    /* Check for other possible errors */
    if (cli->error < 0)
        cli_print_error(cli);

    /* Init SNMP */
    if (cli_snmp_init(username, password) < 0)
        cli->error = CLI_SNMP_INIT_ERROR;

    /* Check for other possible errors */
    if (cli->error < 0)
        cli_print_error(cli);

    /* Set the prompt */
    cli_build_prompt(cli);

    /* Print welcome message */
    printf("\n\t****************************\n");
    printf("\t  wrsw_cli version %s      \n", version);
    printf("\t  Copyright (C) 2011, CERN  \n");
    printf("\t****************************\n\n");

    /* Init main loop */
    cli_main_loop(cli);

    /* Free memory when exiting the main loop */
    if (cli)
        cli_print_error(cli);

	return CLI_ERROR;
}