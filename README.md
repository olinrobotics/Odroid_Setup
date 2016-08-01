# Odroid_Setup
This repository is for the files that we want to put on all of our odroids
so that we can easily use them to run code through ROS as well as solve any
other general Odroid issues we come accross.

The repository also includes a few basic example files for using the Odroid

## What to do with this repository
- Clone this repository to the home directory on both the Odroid and your computer
- Run The Following Script to automate the setup:
   ```bash
   echo 'export ROS_SETUP_PATH="${HOME}/Odroid_Setup/ros"' >> ~/.bashrc
   echo 'source ${ROS_SETUP_PATH}/setup_aliases.sh' >> ~/.bashrc
   echo -e 'function ros_setup(){\nsource ${ROS_SETUP_PATH}/setup.sh\n}' >> ~/.bashrc
   source ~/.bashrc
   ```

### What does this do
In order to run ROS on the odroid and access it from your computer, you need to set the variables `ROS_MASTER_URI` and `ROS_IP` to reference the odroid's IP address as seen from your computer (as opposed to 127.0.0.1).  The shell scripts in this repository (run by `setup.sh`) find the IP address you most likely want to use and set these variables. the line `source ${ROS_SETUP_PATH}/setup.sh` tells the odroid to run these scripts every time a new terminal is opened.

On your computer, the script `setup_aliases.sh` just defines a few aliases for your convenience:
- `set_ros_master_uri <ip>` sets the variable `ROS_MASTER_URI` to reference the input IP address
- `set_ros_vars <ip>` sets both `ROS_MASTER_URI` and `ROS_IP` to reference the input IP address
You need to run one of these commands in each new terminal you open on your computer to communicate with a roscore on the odroid (either will work).

If the roscore is running on your computer but you want the odroid to communicate it, then you need to run `set_ros_vars <your_ip>` in each new terminal you open

note: these aliases are also set on the Odroid with the addition of:
- `set_ros_vars_auto` reruns the automatic variable setup
