function set_ros_master_uri(){
  export ROS_MASTER_URI=http://$1:11311
  echo "set ROS Master to $1"
}

function set_ros_ip(){
  export ROS_IP=$1
  echo "set ROS IP to $1"
}

function set_ros_vars(){
  set_ros_master_uri $1
  set_ros_ip $1
}
