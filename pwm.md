---
title: PWM 
layout: template
filename: pwm
---

## PWM ON THE ODROID

ODROID HAS 2 Hardware PWM output pins, 33 and 19.

To use the PWM output module, follow the instructions below:


1. First, start the PWM module in the kernel. Specify the number of PWM pins to use.

   ```bash
   sudo modprobe pwm-meson npwm=1 #USING 1 PWM PIN (33)
   ```
   
   Alternatively, to use both pins (33 and 19), run:
   
   ```bash
   #sudo modprobe pwm-meson npwm=2 #USING 1 PWM PIN (33, 19)
   ```

2. Begin the PWM control module in the kernel.

   ```bash
   # START PWM CONTROL
   sudo modprobe pwm-ctrl
   ```

3. Change directory to avoid supplying absolute paths.

   ```bash
   # CHANGE DIRECTORY
   cd /sys/devices/platform/pwm-ctrl
   ```

4. Set your parameters.

   ```bash
   export DUTY_CYCLE=102 # 0 ~ 1023
   export FREQUENCY=1024 # IN Hz, 0 ~ 1000000
   ```

5. Launch PWM.

   ```bash
   echo ${DUTY_CYCLE} > duty0
   echo 1 > enable0
   echo ${FREQUENCY} > freq0
   ```

6. When you're done, remove the loaded modules from the kernel.

   ```bash
   sudo modprobe -r pwm-ctrl
   sudo modprobe -r pwm-meson
   ```


