
all build: silentoldconfig

# following targets from Makefile.kconfig
silentoldconfig:
	@mkdir -p include/config
	$(MAKE) -f Makefile.kconfig $@

scripts_basic config %config:
	$(MAKE) -f Makefile.kconfig $@

defconfig:
	@echo "Using wrs_release_defconfig"
	@$(MAKE) -f Makefile.kconfig wrs_release_defconfig

.config: silentoldconfig

