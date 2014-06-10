<?php include 'functions.php'; include 'head.php'; ?>
<body id="epcalib">
<div class="main">
<div class="page">
<div class="header" >
<!--<h1>White-Rabbit Switch Tool</h1>-->
<div class="header-ports" ><?php wrs_header_ports(); ?></div>
<div class="topmenu">
	<?php include 'topmenu.php' ?>
</div>
</div>
<div class="content">
<div class="leftpanel">
<h2>Main Menu</h2>
	<?php include 'menu.php' ?>
</div>
<div class="rightpanel">
<div class="rightbody">
<h1 class="title">Endpoint Calibration<a href='http://www.ohwr.org/projects/white-rabbit/wiki/Calibration' target='_blank'><img align=right src="./img/question.png"></a></h1>
<br>

<?php session_is_started() ?>


	<div>
	<?php 
	
		$file_init  = 'global = {'."\n";
		$file_init .= "\t".'sfp_database_path = "/wr/etc/sfp_database.conf";'."\n";
		$file_init .= '};'."\n\n";

		$file_init .= 'timing =  {'."\n\n";
			
		$file_end = '};'."\n";;
		
		

		// Warning message
		echo "<hr>
				
				NOTE: This action will delete the previous wrsw_hal.conf file. <a href='showfile.php?help_id=file&name=wrsw_hal.conf'
				onClick='showPopup(this.href);return(false);'> (see current configuration) </a>
				<center>*If you do not know how to calibrate endpoints please click on <a href='http://www.ohwr.org/projects/white-rabbit/wiki/Calibration' target='_blank'> here </a>*";
		echo '<br>**all fields are mandatory**</center></div><hr><br><br>';
		
		//echo '<tr><td> <b><center> </center></b></td></tr>';
		
		
		if (empty($_POST['newconf'])){
			// Starting the form (timing + ports)
			echo '<form method="post">';

			echo "<table border='1' align='left' class='altrowstable' id='alternatecolor'>";
			
			
			// Timing values:
			echo '<tr><th>Switch Timing Values</th></tr>';
			echo '<tr><th>PPS Width: </th><th><INPUT type="text" value = "100000" name="pps" > </th></tr>';
			echo '<tr><th>Use NMEA: </th><th><INPUT type="text" value = "1" name="nmea" > </th></tr>';
			echo '<tr><th>Switch Mode: [Master/GrandMaster] </th><th><INPUT type="text" value = "GrandMaster" name="switchmode" > </th></tr>';
			
			// port values:
			for($i=0; $i<18; $i++){

				echo '<tr><th>Endpoint '.($i+1).'</th></tr>';
				if($i<4){ echo '<tr><th>Rx min:</th><th><INPUT type="text" value = "160000" name="rx'.$i.'" > </th></tr>';
				}else{ echo '<tr><th>Rx min:</th><th><INPUT type="text" value = "161200" name="rx'.$i.'" > </th></tr>';}
				echo '<tr><th>Tx min:</th><th><INPUT type="text" value = "0" name="tx'.$i.'" > </th></tr>';
				echo '<tr><th>Mac address:</th><th><INPUT type="text" value = "auto" name="mac'.$i.'" > </th></tr>';
				if($i==0){ echo '<tr><th>Endpoint mode: [wr_slave/wr_master] </th><th><INPUT type="text" value = "wr_slave" name="mode'.$i.'" > </th></tr>';
				}else{  echo '<tr><th>Endpoint mode: [wr_slave/wr_master] </th><th><INPUT type="text" value = "wr_master" name="mode'.$i.'" > </th></tr>';}
				
				
			}
			
			echo '<input type="hidden" name="newconf" value="newconf">';
			echo '</table>';
			echo '<input align="right" type="submit" value="Create new file & Reboot" class="btn">';
			echo '</form>';
			
			
		}
			

		
		if (!empty($_POST['newconf'])){
			$outputfile = $file_init;
			$error = false;
			
			if( empty($_POST['pps']) || empty($_POST['nmea']) || empty($_POST['switchmode'])){
				$error = true;
			}	
			
			// Switch mode must be Master or GrandMaster
			if (!((!strcmp($_POST['switchmode'], "Master")) || !(strcmp($_POST['switchmode'], "GrandMaster")))){
				$error = true;
			}
			
			if(!$error){
				$outputfile .= "\t"."pps_width = ".$_POST['pps']."; -- PPS pulse width"."\n";
				$outputfile .= "--"."\t"."use_nmea = ".$_POST['nmea']."; -- take UTC seconds from NMEA GPS clock connected to /dev/ttyS2"."\n";
				$outputfile .= "--"."\t"."mode = ".'"'.$_POST['switchmode'].'"'."; -- grand-master with external reference"."\n";
				$outputfile .= "};"."\n\n";
			}
				
			$outputfile .= "ports = {"."\n\n";
			for($i=0; $i<18 && (!$error); $i++){
				
				if( empty($_POST['mac'.$i]) || empty($_POST['mode'.$i]) /*|| empty($_POST['tx'.$i])*/ || empty($_POST['rx'.$i])){
					$error = true;
					echo '<br>ERROR!!'.$i."--".empty($_POST['mac'.$i])."--".empty($_POST['mode'.$i])."--".empty($_POST['tx'.$i])."--".empty($_POST['rx'.$i]);
				}
				
				// Switch mode must be Master or GrandMaster
				if (!((!strcmp($_POST['mode'.$i], "wr_master")) || !(strcmp($_POST['mode'.$i], "wr_slave")))){
					$error = true;
				}
				$outputfile .= "\t"."wr".$i." = {"."\n";
				$outputfile .= "\t\t".'phy_rx_min = '.$_POST['rx'.$i].';'."\t"."-- minimal RX latency introduced by the PHY (in picoseconds)"."\n";
				$outputfile .= "\t\t".'phy_tx_min = '.$_POST['tx'.$i].';'."\n\n";
				$outputfile .= "\t\t".'mac_addr = '.'"'.$_POST['mac'.$i].'"'.';'."\n";
				$outputfile .= "\t\t".'mode = '.'"'.$_POST['mode'.$i].'"'.';'."\n";
				$outputfile .= "\t"."};"."\n\n";
			}
			$outputfile .= $file_end;
			
			
		}
		
		
			
		wrs_change_wrfs("rw");

		if(!empty($_POST['newconf']) && !$error){
			//We save the changes in a temporarely file in /tmp
			$file = fopen("/tmp/wrsw_hal.conf","w+");
			fwrite($file,$outputfile);
			fclose($file);
			
			//We move the file to /wr/etc/
			copy('/tmp/wrsw_hal.conf', '/wr/etc/wrsw_hal.conf');
			
			echo '<center><font color="green">File successfully created. Rebooting switch. </font></center>';
			
			wrs_change_wrfs("ro");
			shell_exec("reboot"); 
			
		}else if(!empty($_POST['newconf']) && $error){
			echo '<center><font color="red">WARNING: Conf. file not created. Please fill in all fields</font></center>';
			echo '<center><font color="red">* Switch mode must be Master or GrandMaster </font></center>';
			echo '<center><font color="red">** Endpoint mode must be wr_slave or wr_master </font></center>';
		}
		
		wrs_change_wrfs("ro");
		
		
		
	?>

</div>
</div>
</div>
<div class="footer">
	<?php include 'footer.php' ?>
</div>
</div>
</div>
</body>
</html>
