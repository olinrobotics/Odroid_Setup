---
title: GPS
layout: template
filename: gps
--- 

## Information

Our current GPS module was bought [Here](http://ameridroid.com/products/usb-gps-module).

In case the link goes down, our device uses the Ublox 6010 chipset, with default baud rate of 115200.

The [Quick start guide for Linux](http://odroid.com/dokuwiki/doku.php?id=en:c1_usb_gps) helps with verifying the GPS data, with default UI.

In my experience, I had better success with gpsmon than cgps.

## Setup Guide to publish GPS data to ROS

1. Install The Driver:

   ```bash
   sudo apt-get install ros-indigo-nmea-*
   ```
2. Make ROS Recognize the new package:

   ```bash
   roscd nmea_navsat_driver
   ```

3. Run Roscore In a background process:

   ```bash
   roscore &
   ```

4. Run the NMEA publisher:

   ```
   rosrun nmea_navsat_driver nmea_serial_driver _port:=/dev/ttyACM0 _baud:=115200 #default baud rate is 115200
   ```

5. (TIP) If publishing to ROS fails, check that the GPS device publishes the correct NMEA DATA over the serial:

   Python Script

   ```python
   import serial

   with serial.Serial('/dev/ttyACM0',115200) as ser:
      while ser._isOpen:
         print(ser.readline())
   ```
