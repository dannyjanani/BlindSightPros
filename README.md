# BlindSightPros

## Project Overview

Inspired by watching a blind person walk from the train station to the bank and inside to make a deposit, we were tasked to create a device that will help a visually disabled person walk from one location to another unassisted. Given a tight budget we had to create a wearable that detects objects in front or on the sides of a person. Google maps navigation often tells you "Turn in 100 feet". We wanted to have a similar concept. There were a few challenges though. A blind-folded person, used for testing, often does not walk straight as he is not used to it. We laser printed a box with three holes in it for sensors, with a rope tied to the person for him to have his hands free. We placed an [ultrasonic] sensor in each of the holes, one pointed ahead, right, and left to cover all directions. Inside the box was a [microcontroller] with a [buzzer] inside, to tell the user which direction and how far the obstuction is. The frequency of the buzzer would be different depending on the direction the obstruction is, making a different sound. If the obstruction was close, the user would hear a quick beep, whereas if it was further the beep would be slower, kind of like a backup camera on modern-day cars.

## Project Details

* The first microcontroller was used to detect objects (attached to shirt)
  * Using 3 Ultrasonic sensors, placed in front and on the sides of the person, the person would receive feedback of any    obstructions.
  * Based on the direction an obstruction is detected, a different sound will be played telling the person where the obstruction is. 
  * The beep would get faster and faster till it's a steady beat indicating how close the object is.
    * The concept is similar to a car's backup camera beeping.

* Another microcontroller was used to track foot steps and direction (attached to pants)
  * An accelerometer was connected to detect and make sure the person is walking straight.
    * If one wears a blindfold, it's very hard to walk straight and track direction, so we had to include this feature.
    * If the person is veering off course, vibrators placed on each hand will tell which way the person needs to turn.
    * It would vibrate on left hand if he/she needs to veer left and right hand if he/she needs to veer right.
  * A Force-Sensitive Resistor (FSR) was connected to detect footsteps.
    * If the navigation says, in 50 feet turn left, the left vibrator would buzz.
    * If the navigation says, in 50 feet turn right, the right vibrator would buzz.
    
# Skills Learned/Improved
