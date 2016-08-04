---
title: AR Pose
layout: template
filename: arpose
--- 

## Demo

<video controls width="100%" height="100%">
	Your Browser Does Not Support The Video Tag.
	<source src="videos/arpose.mp4" type="video/mp4">
</video>

## Setup ARPOSE 

### Installing AR_POSE
1. If you plan on visualizing the output of ar_pose with rviz, you must fix libpcre:

   ```bash
   export lib_src="http://ports.ubuntu.com/pool/main/p/pcre3"
   mkdir -p ~/libpcre && cd ~/libpcre
   wget ${lib_src}/libpcre3-dev_8.35-7.1ubuntu1_armhf.deb
   wget ${lib_src}/libpcre3_8.35-7.1ubuntu1_armhf.deb
   wget ${lib_src}/libpcre16-3_8.35-7.1ubuntu1_armhf.deb
   wget ${lib_src}/libpcre32-3_8.35-7.1ubuntu1_armhf.deb
   wget ${lib_src}/libpcrecpp0v5_8.35-7.1ubuntu1_armhf.deb
   unset lib_src
   sudo dpkg -i *.deb
   sudo apt-get -f install
   ```

   I didn't quite test if the installation would work without error.
   If you encounter an error, run:

   ```bash
   dpkg -l | grep pcre | awk '{print $3}'
   ```

   and check that all of them start with 2.
   otherwise, remove all the packages with

   ```bash
   dpkg -l | grep pcre | awk '{print $2}' | xargs -i sudo dpkg -r {}
   ```

   and try to install again.

   If dependency problems prevent the removal of the above libraries, try running the following instead:

   ```bash
   sudo apt-get remove --purge libpcre*
   ```

   Take note of the libraries that are removed and reinstall them after you fix the package.

2. Before anything else, run:

   ```bash
   sudo apt-get update
   sudo apt-get install freeglut3-dev
   ```

   I currently don't remember where glut library was needed, so just get it at the beginning.

3. You should have installed ros and initialized your catkin workspace. Make sure you have the following:

   ```bash
   source ~/catkin_ws/devel/setup.bash
   ```

   in your ~/.bashrc, so that ROS knows where your workspace is.

   If your catkin workspace is not in your home directory, replace the path above, and any related paths hereafter, with wherever you have created your catkin workspace.

4. Download ar_tools package from the repository.

   ```bash
   rosmake rviz rosbag
   cd ~/catkin_ws/src
   git clone https://github.com/ar-tools/ar_tools.git
   ```

5. Run the script to fetch the ar marker data.

   ```bash
   roscd ar_pose/demo
   ./setup_demos
   ```

6. Install Camera Drivers.

   ```bash
   sudo apt-get install ros-indigo-libuvc*
   sudo apt-get install ros-indigo-uvc-camera
   ```

7. Build artoolkit first, to prevent errors.

   ```bash
   cd ~/catkin_ws
   catkin_make --only-pkg-with-deps artoolkit
   ```

8. In order to avoid inexplicable crashes, comment out everything related to ar_multi.

   ```bash
   roscd ar_pose
   vim CMakeLists.txt
   ```

   It should look like:

   ```bash
   #add_executable(ar_multi
   #	src/ar_multi.cpp
   #	src/object.cpp
   #)
   #target_link_libraries(ar_multi
   #	${catkin_LIBRARIES}
   #)
   #add_dependencies(ar_multi
   #	${PROJECT_NAME}_generate_messages_cpp
   #	${artoolkit_EXPORTED_TARGETS}
   #)
   
   install(TARGETS ar_single
     RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
   )
   
   #install(TARGETS ar_multi
   #  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
   #)
   ```

9. Make the package with flags to remove the whitelist for artoolkit.

   ```bash
   cd ~/catkin_ws
   catkin_make -DCATKIN_WHITELIST_PACKAGES=""
   ```

### Calibrating the camera

1. Plug in your oCam to a usb port and verify the connection.

   ```bash
   dmesg | tail
   lsusb
   ls /dev/video*
   ```

   Example output:

   ```bash
   [12697.053929] wlan0: Limiting TX power to 15 (15 - 0) dBm as advertised by f8:c0:01:a1:37:45
   [14905.712196] usb 3-2: new SuperSpeed USB device number 2 using xhci_hcd
   [14905.728884] usb 3-2: LPM exit latency is zeroed, disabling LPM.
   [14905.729589] usb 3-2: New USB device found, idVendor=04b4, idProduct=00f9
   [14905.729591] usb 3-2: New USB device strings: Mfr=1, Product=2, SerialNumber=3
   [14905.729593] usb 3-2: Product: oCam-5CRO-U
   [14905.729594] usb 3-2: Manufacturer: WITHROBOT Inc.
   [14905.729595] usb 3-2: SerialNumber: SN_2736C011
   [14905.729966] uvcvideo: Found UVC 1.00 device oCam-5CRO-U (04b4:00f9)
   [14905.731167] input: oCam-5CRO-U as /devices/pci0000:00/0000:00:14.0/usb3/3-2/3-2:1.0/input/input19
   Bus 001 Device 005: ID 0a5c:5800 Broadcom Corp. BCM5880 Secure Applications Processor
   Bus 001 Device 004: ID 0c45:6709 Microdia 
   Bus 001 Device 003: ID 8087:0a2a Intel Corp. 
   Bus 001 Device 002: ID 8087:8001 Intel Corp. 
   Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
   Bus 003 Device 002: ID 04b4:00f9 Cypress Semiconductor Corp. 
   Bus 003 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
   Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
   /dev/video0
   ```

2. Install the packages for handling images over ros and camera calibration.

   ```bash
   sudo apt-get install ros-indigo-image-proc
   rosdep install image_proc
   sudo apt-get install ros-indigo-camera-calibration
   ```

3. Start roscore, and leave it running throughout this instruction.

   ```bash
   roscore
   ```

4. Begin publishing the data from the camera to ROS in a terminal.

   ```bash
   rosrun uvc_camera uvc_camera_node _device:="/dev/video0" 
   ```

5. Open another tab in your terminal (CTRL-SHIFT-T) and begin Calibrating.

   ```bash
   rosrun camera_calibration cameracalibrator.py --size 8x6 --square 0.496 image:=/image_raw camera:=/
   ```

   A small window would appear showing the camera. The window will reopen to a bigger display if you close it, but **DO NOT CLOSE THIS WINDOW**. The buttons are identified by coordinates, and the coordinates stay the same even if your window becomes larger than the original one, which makes it very difficult to find the CALIBRATE button after you gathered all your samples.

   When calibrating, it takes about 40 samples. It may take more, depending on the quality of each sample.

   To obtain a variety of samples with X,Y,Z(size) and Skew values, move the Chessboard around in different orientations.

   Calibrating on the ODROID is slow, so you might want to calibrate on your computer and only copy the camera.yaml over to the odroid (not tested).

   When enough samples are gathered, the CALIBRATE button will turn green. Press on it to view the results.

   When you're satisfied, click SAVE and COMMIT. In the first terminal, take note of the path where camera.yaml is saved.

6. Move the camera.yaml file to the default directory where ar_pose looks for:

   ```bash
   mv ~/.ros/camera_info/camera.yaml /opt/ros/indigo/share/uvc_camera/camera_calibration.yaml
   ```

   Alternatively, edit your ar_pose_single.launch file and edit the camera_info_url parameter to point to the absolute **URL** of your .yaml file.
   For instance, it may look like **file:///home/odroid/.ros/camera_info/camera.yaml**.

### Running ar_pose 

1. Open the launch configuration as follows:

   ```bash
   roscd ar_pose/launch
   vim ar_pose_single.launch
   ```

2. In ar_pose_single.launch, change camera_node to uvc_camera_node.

   Then, change the device parameter to your camera device input (e.g. /dev/video0).

   Finally, check the width and height parameters under uvc_camera_node and verify that they match the ones in the camera.yaml file.

   (camera.yaml file is the one produced by camera_calibration)

   For me, the resolution was 640x480.

3. To run ar_pose:

   ```bash
   roslaunch ar_pose ar_pose_single.launch
   ```

### If ar_pose still fails 

1. To view images over ros topic, install:

   ```bash
   sudo apt-get install ros-indigo-image-view
   ```

2. Open a terminal and launch a camera instance.

   ```bash
   export ROS_NAMESPACE=my_camera
   rosrun uvc_camera uvc_camera_node _device:="/dev/video0"_width:=${WIDTH} _height:=${HEIGHT} _camera_info_url:="file:///home/odroid/path/to/yaml/file/camera_calibration.yaml"
   ```

   Note that you have to provide the *camera_info_url* to match the path in **YOUR** odroid. The script will not run properly as written.

3. Check that the camera calibration info was properly loaded.

   ```bash
   rostopic echo /my_camera/camera_info
   verify that most of the parameters are nonzero.
   ```

4. Open up another tab in your terminal and run image_proc node.

   ```bash
   export ROS_NAMESPACE=my_camera
   rosrun image_proc image_proc image:=/image_raw
   ```

5. Open up another tab in your terminal to view the rectified image.

   ```bash
   rosrun image_view image_view image:=/my_camera/image_rect
   verify that you're getting an image.
   ```

6. To view the connections between the nodes and the topics, run:

   ```bash
   rqt_graph
   ```
