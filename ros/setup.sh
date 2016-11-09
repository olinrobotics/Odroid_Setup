function ros_get_ip(){
	echo $(ifconfig $1 2>/dev/null | awk '/inet addr:/ {print $2}' | sed 's/addr://')
}

function set_ros_master_uri(){
	export ROS_MASTER_URI=http://$1:11311
}
function set_ros_vars(){
	export ROS_IP=$1
	ros_set_master_uri $ROS_IP
	echo "ROS_IP =" $ROS_IP
	echo "ROS_MASTER_URI =" $ROS_MASTER_URI
}

function ros_find_useful_ip(){
	local ip
	#wlan0 eth0 wlan1, order of importance
	#break prematurely if a "more important" device is found
	for dev in wlan0 eth0 wlan1; do
		ip=$(ros_get_ip $dev)
		if [[ ! -z $ip && $(ping -c 1 $ip 1>/dev/null; echo $?) == 0 ]]; then
			break;
		fi
	done
	echo $ip
}


function ros_auto_set_vars(){
	set_ros_vars $(ros_find_useful_ip)
}

ros_auto_set_vars
