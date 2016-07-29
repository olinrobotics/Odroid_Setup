echo setting ROS IP and MASTER_URI to $1
export ROS_IP=$1
export ROS_MASTER_URI=http://$1:11311
