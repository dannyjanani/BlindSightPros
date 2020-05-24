# BlindSightPros

## Project Overview

Inspired by watching a blind person walk from the train station to the bank and inside to make a deposit, we were tasked to create a device that will help a visually disabled person walk from one location to another unassisted. Given a tight budget we had to create a wearable that detects objects in front or on the sides of a person. Google maps navigation often tells you "Turn in 100 feet". We wanted to have a similar concept. There were a few challenges though. A blind-folded person, used for testing, often does not walk straight as he is not used to it. We laser printed a box with three holes in it for sensors, with a rope tied to the person for him to have his hands free. We placed an [ultrasonic](https://www.keyence.com/ss/products/sensor/sensorbasics/ultrasonic/info/) sensor in each of the holes, one pointed ahead, right, and left to cover all directions. Inside the box was a [microcontroller](https://internetofthingsagenda.techtarget.com/definition/microcontroller) with a [buzzer](https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45) inside, to tell the user which direction and how far the obstuction is. The frequency of the buzzer would be different depending on the direction the obstruction is, making a different sound. If the obstruction was close, the user would hear a quick beep, whereas if it was further the beep would be slower, kind of like a backup camera on modern-day cars. Another part of this project was to track steps and ensure the user was walking in a straight path. We placed a box near the waist where we placed an [accelerometer](https://www.livescience.com/40102-accelerometers.html) and wires down to the bottom of the shoe with an [FSR](https://learn.adafruit.com/force-sensitive-resistor-fsr/using-an-fsr) (Force Sensitive Resistor) to track steps. We also have vibrators placed on each wrist, telling the user to turn right or left. When the FSR reaches a certain step count (calibrated according to user's step size), it would set off the vibrator in the direction the user needs to turn. The user, at any time, can press a button on this box, to ensure he is walking straight. If he's not, it would vibrate telling him the direction he needs to turn till he gets to the right direction.

Using these two microcontrollers, we were able to direct the user to the endpoint, safely.

## Project Requirements

* Needs to be universal.
* Navigate the user from Point A to Point B without hitting obstructions.
* Give user feedback to know where the obstuctions are and which direction they should go.
* Allow user to have both hands free for holding things.
* Ability to replace and enhance the "walking stick".
    
## What I used?
