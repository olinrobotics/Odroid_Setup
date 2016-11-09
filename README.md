# Odroid_Setup
This repository is for the files that we want to put on all of our odroids
so that we can easily use them to run code through ROS as well as solve any
other general Odroid issues we come accross.

The repository also includes a few basic example files for using the Odroid

## What to do with this repository
- Clone this repository to the home directory on both the Odroid and your computer

   ```bash
   cd ${HOME}
   git clone git@github.com:olinrobotics/Odroid_Setup.git
   ```

- Run the following lines in the terminal on the odroid to automate the setup:

   ```bash
   echo 'source ${HOME}/Odroid_Setup/ros/setup.sh' >> ~/.bashrc
   source ~/.bashrc
   ```

   Now all the odroid setup should run automatically.

- Run the following lines in your terminal to set some convenient aliases:
	```bash
	echo 'source ${HOME}/Odroid_Setup/ros/setup_aliases.sh
	source ~/.bashrc
	```

	Now you get two convenient aliases for setting ROS related IP addresses on your computer.

### What does this do
In order to run ROS on the odroid and access it from your computer, you need to set the variables `ROS_MASTER_URI` to reference the odroid's IP address as seen from your computer (as opposed to 127.0.0.1), and `ROS_IP` to the IP address of your computer as seen by the odroid (note, `ROS_IP` only matters if you are running `roscore` on your computer).  The shell scripts in this repository (run by `setup.sh`) find the IP address you most likely want to use and set these variables, however, it's assumptions only work well for the odroid. the line `source ${HOME}/Odroid_Setup/ros/setup.sh` tells the odroid to run these scripts every time a new terminal is opened.

On your computer, the script `setup_aliases.sh` just defines a few aliases for your convenience:
- `set_ros_master_uri <ip>` sets the variable `ROS_MASTER_URI` to reference the input IP address
  - this should always reference the IP address of the computer running roscore
- `set_ros_ip <ip>` sets `ROS_IP` to reference the input IP address
  - this should always reference the IP address of the computer you run it from
- `set_ros_vars <ip>` sets both `ROS_MASTER_URI` and `ROS_IP` to reference the input IP address.
You need to run these commands in every new terminal you open on your computer (if roscore is on the odroid, you only need to run `set_ros_master_uri <ip>`.

If the roscore is running on your computer but you want the odroid to communicate it, then you need to run `set_ros_vars <your_ip>` in each new terminal you open.

note: these aliases are also set on the Odroid with the addition of:
- `ros_get_ip` prints all of the available ips
- `ros_find_useful_ip` prints the most useful ip
- `ros_auto_set_vars` reruns the automatic variable setup
