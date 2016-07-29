#!/bin/bash
#export wifi_device=wlan1
wifi_device=$1
sudo ip link set ${wifi_device} down
sudo iwconfig ${wifi_device} mode ad-hoc
sudo iwconfig ${wifi_device} channel 4
sudo iwconfig ${wifi_device} essid 'ad-hoc'
sudo iwconfig ${wifi_device} key 1234567890
sudo ip link set ${wifi_device} up
sudo ip route flush dev ${wifi_device}
sudo ip addr flush dev ${wifi_device}
sudo ip addr add 169.254.34.2/24 dev ${wifi_device}
