#!/usr/bin/perl -w

# This project is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# IT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Deviation.  If not, see <http://www.gnu.org/licenses/>.
#
# This file is the work of and copyright Cameron Weeks <th9xer@gmail.com>
# http://code.google.com/p/rc-ppm-2-spi/
 

$LOGFILE = "nanostick_spi.csv";
open(LOGFILE) or die("Could not open log file.");
$packet_no_last="0";
$packet_no="0";
$time=0;
$time_last=0;
$i = 0;
$j = 0;
$line_no = 0;
$rssi_mute = 0;
$frame_delay = (0.23/1000); #milliseconds



foreach $line (<LOGFILE>)
{

	$line_no++;
	next if $line_no ==1; #skip titles on first line

    ($time, $packet_no, $mosi, $miso) = split(',',$line);
	next unless defined $packet_no; #skip last line feed if it exists

	#print $line_no, " ";
	if ($packet_no ne $packet_no_last)
		{
		$packet_no_last = $packet_no;

		# convert 4bit nibbles in to 8bit bytes
		for ($j=0,$k=0; $j<$i; $j++)
			{
			$temp1 = substr($packet[$j], 2, 1);
			$j++;
			if ($j<$i) {$temp2 = substr($packet[$j], 2, 1);}
			else {$temp2 = "0";}
			$decoded_packet[$k] = $temp1.$temp2;
			$k++;
			}
		# print the decoded packet

		if ($k==1 && $rssi_mute==0) {print strobe_eval($decoded_packet[0]), " ";}
		#if ($k==1) {$temp=1;}

		else
			{
			
			if ($rssi_count && ($decoded_packet[0] ne "5D"))
				{
				print "RSSI = ".($rssi/$rssi_count)."\n";
				$rssi=0;
				$rssi_count=0;
				$rssi_mute=0;
				}
				
			if ($decoded_packet[0] eq "5D")
				{
				$rssi += hex($decoded_packet[1]);
				$rssi_count++;
				$rssi_mute=1;
				}
			if ($rssi_mute==0)
				{
				print command_eval($decoded_packet[0]), " ";
				for ($j=1; $j<$k; $j++)
					{
					print $decoded_packet[$j], " ";
					}
				}
			}
		if ($rssi_mute==0) {print "\n";}

		$i=0;
		if ($rssi_mute==0)
			{
			if (($time - $time_last) > $frame_delay) {print "\n";}
			}
		}

	$time_last = $time;
	$packet[$i] = $mosi;
	$i++;
}

#print the last packet
#if ($i==1) {print strobe_eval($packet[0]);}
for ($j=0; $j<$i; $j++)
	{
	print $packet[$j], " ";
	}
print "\n";

close(LOGFILE);
exit;

sub strobe_eval
{
if    ($_[0] eq "80") {return("STROBE Sleep       ");}
elsif ($_[0] eq "90") {return("STROBE Idle        ");}
elsif ($_[0] eq "A0") {return("STROBE Standby     ");}
elsif ($_[0] eq "B0") {return("STROBE PLL         ");}
elsif ($_[0] eq "C0") {return("STROBE Rx          ");}
elsif ($_[0] eq "D0") {return("STROBE Tx          ");}
elsif ($_[0] eq "E0") {return("STROBE FIFO W Rst  ");}
elsif ($_[0] eq "F0") {return("STROBE FIFO R Rst  ");}
else {return($_[0]);}
}

sub command_eval
{
$register ="";
$rw = "";

if   (hex($_[0]) & hex(40)) {$rw="RD ";}
else {$rw="WR ";}

$temp = hex($_[0]) & ~(hex(40));
$temp = uc(sprintf("%02x",$temp));
#print "temp ".$temp."\n";

if    ($temp eq "00") {$register="00_MODE          ";}
elsif ($temp eq "01") {$register="01_MODE_CONTROL  ";}
elsif ($temp eq "02") {$register="02_CALC          ";}
elsif ($temp eq "03") {$register="03_FIFOI         ";}
elsif ($temp eq "04") {$register="04_FIFOII        ";}
elsif ($temp eq "05") {$register="05_FIFO_DATA     ";}
elsif ($temp eq "06") {$register="06_ID_DATA       ";}
elsif ($temp eq "07") {$register="07_RC_OSC_I      ";}
elsif ($temp eq "08") {$register="08_RC_OSC_II     ";}
elsif ($temp eq "09") {$register="09_RC_OSC_III    ";}
elsif ($temp eq "0A") {$register="0A_CK0_PIN       ";}
elsif ($temp eq "0B") {$register="0B_GPIO1_PIN1    ";}
elsif ($temp eq "0C") {$register="0C_GPIO2_PIN_II  ";}
elsif ($temp eq "0D") {$register="0D_CLOCK         ";}
elsif ($temp eq "0E") {$register="0E_DATA_RATE     ";}
elsif ($temp eq "0F") {$register="0F_PLL_I         ";}
elsif ($temp eq "10") {$register="10_PLL_II        ";}
elsif ($temp eq "11") {$register="11_PLL_III       ";}
elsif ($temp eq "12") {$register="12_PLL_IV        ";}
elsif ($temp eq "13") {$register="13_PLL_V         ";}
elsif ($temp eq "14") {$register="14_TX_I          ";}
elsif ($temp eq "15") {$register="15_TX_II         ";}
elsif ($temp eq "16") {$register="16_DELAY_I       ";}
elsif ($temp eq "17") {$register="17_DELAY_II      ";}
elsif ($temp eq "18") {$register="18_RX            ";}
elsif ($temp eq "19") {$register="19_RX_GAIN_I     ";}
elsif ($temp eq "1A") {$register="1A_RX_GAIN_II    ";}
elsif ($temp eq "1B") {$register="1B_RX_GAIN_III   ";}
elsif ($temp eq "1C") {$register="1C_RX_GAIN_IV    ";}
elsif ($temp eq "1D") {$register="1D_RSSI_THOLD    ";}
elsif ($temp eq "1E") {$register="1E_ADC           ";}
elsif ($temp eq "1F") {$register="1F_CODE_I        ";}
elsif ($temp eq "20") {$register="20_CODE_II       ";}
elsif ($temp eq "21") {$register="21_CODE_III      ";}
elsif ($temp eq "22") {$register="22_IF_CALIB_I    ";}
elsif ($temp eq "23") {$register="23_IF_CALIB_II   ";}
elsif ($temp eq "24") {$register="24_VCO_CURCAL    ";}
elsif ($temp eq "25") {$register="25_VCO_SBCAL_I   ";}
elsif ($temp eq "26") {$register="26_VCO_SBCAL_II  ";}
elsif ($temp eq "27") {$register="27_BATTERY_DET   ";}
elsif ($temp eq "28") {$register="28_TX_TEST       ";}
elsif ($temp eq "29") {$register="29_RX_DEM_TEST_I ";}
elsif ($temp eq "2A") {$register="2A_RX_DEM_TEST_II";}
elsif ($temp eq "2B") {$register="2B_CPC           ";}
elsif ($temp eq "2C") {$register="2C_XTAL_TEST     ";}
elsif ($temp eq "2D") {$register="2D_PLL_TEST      ";}
elsif ($temp eq "2E") {$register="2E_VCO_TEST_I    ";}
elsif ($temp eq "2F") {$register="2F_VCO_TEST_II   ";}
elsif ($temp eq "30") {$register="30_IFAT          ";}
elsif ($temp eq "31") {$register="31_RSCALE        ";}
elsif ($temp eq "32") {$register="32_FILTER_TEST   ";}
else {$register=$_[0];}

return ($rw.$register);
}