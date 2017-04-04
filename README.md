# jetsonGPIO
A straightforward library to interface with the Jetson TK1 Development Kit GPIO  pins.

Based on Software by RidgeRun & Jetson Hacks
https://developer.ridgerun.com/wiki/index.php/Gpio-int-test.c
 * Copyright (c) 2011, RidgeRun
 * All rights reserved.

http://www.jetsonhacks.com/nvidia-jetson-tx1-j21-header-pinout/

# Purpose
These libraries are going to be used to power the fundamental gpio usage of the Jetson TX1. Expirements have shown that these libraries are compatable to use on Raspberry Pi and most likely any other linux based system.
That being said, this program is used to aquire distance mesurements from Ultrasonic Sensors. This will work in parrarlel with an I2C Haptic Motor Controller and USB Cameras.

exampleGPIApp.cpp describes usage of Ultrasonic Sensors with visual feedback through attached LEDs
