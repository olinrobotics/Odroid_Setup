---
title: WiFi
layout: template
filename: wifi
--- 

## Setting Up WiFi on the ODROID with a USB Dongle


1. First, install the necessary tools:

   ```bash
   sudo apt-get install wireless-tools wpasupplicant
   ```

2. Check that the ODROID recognizes the device and loads the proper driver:

   ```bash
   dmesg | tail
   ```

3. Scan for available networks to check that the device functions properly.

   ```bash
   sudo iwlist wlan0 scan
   ```

4. Configure the network interfaces. In order to access the file, you need to become root. Type the password when prompted.

   ```bash
   sudo -s
   echo -e "\nauto wlan0 \niface wlan0 inet dhcp \n\twpa-ssid OLIN-ROBOTICS\n\twpa-psk R0B0TS-RULE" >> /etc/network/interfaces
   ```

5. Configure the WPA credentials for your network.

   ```bash
   wpa_passphrase  OLIN-ROBOTICS >> /etc/wpa_supplicant/wpa_supplicant_OLIN-ROBOTICS.conf 
   ```

6. Try to connect to network with the given configuration. You should see an output with UP highlighted.

   ```bash
   sudo wpa_supplicant -B -D wext -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant_OLIN-ROBOTICS.conf 
   ip link show wlan0 | grep UP
   ```
   
   Tip : if you messed up and have multiple processes running wpa_supplicant, get rid of them:

   ```bash
   ps -ef | grep  "wpa_"
   sudo kill $(pgrep -f "wpa_supplicant -B")
   ```

7. Setup IP with the router.

   ```bash
   sudo dhclient -v -r wlan0
   ```

8. Restart wlan0.

   ```bash
   sudo ifdown wlan0 && sudo ifup wlan0
   ```

9. Check network connection status.

   ```bash
   iwconfig # CHECKS WIRELESS DEVICE STATUS
   ifconfig # CHECKS GENERAL NETWORK STATUS
   ```

2. Check subnet connectivity. Your computer should be connected to OLIN-ROBOTICS, if you configured your WPA credentials with OLIN-ROBOTICS.

   ```bash
   ping <your_computer_ip>
   ```

2. Check External Network Connectivity. Disable network sharing via ethernet cable if you had it set up, to verify the connection.

   ```bash
   ping www.google.com
   ```

