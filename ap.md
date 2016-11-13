---
title: AP
layout: template
filename: ap
---

## References

[Stack Overflow](https://askubuntu.com/questions/180733)
[PixHawk Documentation](https://pixhawk.org/peripherals/onboard_computers/access_point)
[Ras-Pi Documentation](https://xmodulo.com/raspberry-pi/wifi-access-point.html)

## Installing Relevant Packages

```bash
sudo apt-get install hostapd udhcpd
```

### Fixing HostAPD for RTL8188/RTL8192CU Drivers

(This is only applicable if your Wifi dongle uses the RTL8192 driver)

Check with:

```bash
dmesg | grep 8192
[    8.135523@3] usbcore: registered new interface driver rtl8192cu
```

Install new version of hostapd:

```bash
wget https://github.com/jenssegers/RTL8188-hostapd/archive/v2.0.tar.gz
tar -zxvf v2.0.tar.gz
cd RTL8188-hostapd-2.0/hostapd/
sudo make && sudo make install
```

## Configuring hostapd/ udhcpd

Copy the contents of [hostapd.conf](AP/hostapd.conf) to /etc/hostapd/hostapd.conf
Copy the contents of [udhcpd.conf](AP/udhcpd.conf) to /etc/udhcpd.conf
Copy the contents of [hostapd](AP/hostapd) to /etc/default/hostapd
Copy the contents of [udhcpd](AP/udhcpd) to /etc/default/udhcpd

As for the details of each lines in the file, refer to the [References](#References).

## Starting the AP
Make sure that no other instances are running:

```bash
pgrep udhcpd
pgrep hostapd
## should output nothing
```

Start udhcpd (handle ip addresses, etc.) and hostapd (access point)

```bash
sudo service udhcpd start
sudo service hostapd start
```

## Configuring on Startup


