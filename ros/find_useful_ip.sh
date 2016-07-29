#!/bin/bash
ip=$(get_ip.sh wlan1)
if [[ ! -z $ip ]];then final_ip=$ip;fi
ip=$(get_ip.sh eth0)
if [[ ! -z $ip ]];then final_ip=$ip;fi
ip=$(get_ip.sh wlan0)
if [[ ! -z $ip ]];then final_ip=$ip;fi
echo $final_ip
