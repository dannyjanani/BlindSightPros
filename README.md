# BlindSightPros

A device to help those who are visually disabled, navigate without the use of a walking stick.

## Project Overview

Inspired by watching a blind person walk from the train station to the bank and inside to make a deposit, we were tasked to create a device that will help a visually disabled person walk from one location to another unassisted. Given a tight budget we had to create a wearable that detects objects in front or on the sides of a person. Google maps navigation often tells you "Turn in 100 feet". We wanted to have a similar concept. There were a few challenges though. A blind-folded person, used for testing, often does not walk straight as he is not used to it. We laser printed a box with three holes in it for sensors, with a rope tied to the person for him to have his hands free. We placed an [ultrasonic](https://www.keyence.com/ss/products/sensor/sensorbasics/ultrasonic/info/) sensor in each of the holes, one pointed ahead, right, and left to cover all directions. Inside the box was a [microcontroller](https://internetofthingsagenda.techtarget.com/definition/microcontroller) with a [buzzer](https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45) inside, to tell the user which direction and how far the obstuction is. The frequency of the buzzer would be different depending on the direction the obstruction is, making a different sound. If the obstruction was close, the user would hear a quick beep, whereas if it was further the beep would be slower, kind of like a backup camera on modern-day cars. Another part of this project was to track steps and ensure the user was walking in a straight path. We placed a box near the waist where we placed an [accelerometer](https://www.livescience.com/40102-accelerometers.html) and wires down to the bottom of the shoe with an [FSR](https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr) (Force Sensitive Resistor) to track steps. We also have vibrators placed on each wrist, telling the user to turn right or left. When the FSR reaches a certain step count (calibrated according to user's step size), it would set off the vibrator in the direction the user needs to turn. The user, at any time, can press a button on this box, to ensure he is walking straight. If he's not, it would vibrate telling him the direction he needs to turn till he gets to the right direction.

Using these two microcontrollers, we were able to direct the user to the endpoint, safely.

## Project Goals

* Team of 3 people.
* Needs to be universal.
* Navigate the user from Makerspace are to the cafeteria without hitting obstructions.
* Buy pizza slice in the cafeteria.
* Give user feedback to know where the obstuctions are and which direction they should go.
* Allow user to have both hands free for holding things.
* Ability to replace and enhance the "walking stick".
* Develop electronic/embedded system that would help complete the task.
* The user must be blindfolded the entire time, no visual feedback allowed.
* Teammates are not allowed to help the person navigate.
* No direct tactile feedback (you can use a stick, but cannot feel with a stick, placing a sensor on it is fine).

## Provided Materials

* 3x [HC-SR04 Ultrasonic Sensors](https://www.adafruit.com/product/3942)
* 1x [GP2Y0A21TK0F IR Sensor](https://www.adafruit.com/product/164)
* 1x [Stackable Proto Shield](https://www.adafruit.com/product/2077)
* 5x [Screw Terminal Blocks](https://www.walmart.com/ip/20PCS-300V-10A-3-50mm-Pitch-2P-Male-PCB-Screw-Terminal-Block-Connector-Green/871518443?wmlspartner=wlpa&selectedSellerId=571&adid=22222222227155079247&wl0=&wl1=g&wl2=c&wl3=266340381064&wl4=aud-430887228898:pla-439086344342&wl5=9004364&wl6=&wl7=1023239&wl8=&wl9=pla&wl10=111838760&wl11=online&wl12=871518443&veh=sem)
* Unlimited Maker space resources (3d printing, laser cutting, etc.)
* $50 Budget per team used for:
  * 2x [Adafruit METRO 328](https://www.adafruit.com/product/2488)
  * 2x [Vibrating Mini Motor Disk](https://www.adafruit.com/product/1201)
  * 1x [Piezo Buzzer](https://www.adafruit.com/product/160)
  * 1x [Accelerometer](https://www.adafruit.com/product/1120)
  * 1x [FSR](https://www.adafruit.com/product/166) (Force Sensitive Resistor)
  * 1x [Jumper Cables](https://www.adafruit.com/product/759)
  * 1x [Breadboard](https://www.adafruit.com/product/64)
  * 1x Pair of gloves
  * 1x Rope

## What I used?

* Prototyping:
  * Laser Cutting
  * 3D Printing
  * Soldering
  
* Materials:
  * See "Provided Materials" Section
  
* Software:
  * C
  * Arduino IDE
  * SolidWorks
  * Ultimaker Cura
