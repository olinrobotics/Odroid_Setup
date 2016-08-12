---
title: Cross Compile 
layout: template
filename: cross_compile
--- 

 - Installing Cross-compilers

   ```bash
   sudo apt-get update
   sudo apt-get install gcc-arm-linux-gnueabihf
   sudo apt-get install binutils-arm-linux-gnueabi
   ```

 - Write a simple test program

   ```bash
   printf '#include<stdio.h>\n\nint main(){\n\tprintf(\"Hello,World!\\n\");\n\treturn 0;\n}' > test.c
   ```

 - Compile test.c to test.o

   ```bash
   arm-linux-gnueabihf-gcc test.c -o test.o
   ```

 - Query the information (it should indicate 32-bit ARM executable)

   ```bash
   file test.o 
   ```

 - Find the ip of odroid to connect via eth0 (replace eth0 with whichever connection you have)

   ```bash
   export eth0_ip=$(ifconfig eth0 2>/dev/null | awk '/inet addr:/ {print $2}' | sed 's/addr://')
   nmap ${eth0_ip}/24
   ```

 - Copy the binary to the odroid (replace the ip with whichever ip you found)

   ```bash
   scp test.o odroid@10.42.0.220:~/
   ```

 - In the odroid,

   ```bash
   ~/test.o
   ```

 - The output should be "Hello,world!\n".
