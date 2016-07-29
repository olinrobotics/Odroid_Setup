---
title: ROS
layout: template
filename: ros
--- 

## Odroid and ROS
We used [these instructions](http://wiki.ros.org/indigo/Installation/UbuntuARM) to install ROS on the ODROID.  They worked fine, so you should be able to just follow them.

Once ROS is installed, you can run roscore as well as any programs which use ROS, but more setup is needed to be able to communicate with a roscore on the odroid from another computer.  We set up a [github repository](https://github.com/olinrobotics/Odroid_Setup) with some shell scripts to automatically setup the odroid to communicate with other computers.  These scripts set the `ROS_MASTER_URI` and `ROS_IP` variables to point at the correct IP address so that other computers can see the roscore running on the odroid.  Instructions for using these scripts are in that repository's README.


