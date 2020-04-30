# BlindSightPros

Inspired by watching a blind person walk from the train station to the bank and inside to make a deposit, we were tasked to create a device that will help a visually disabled person walk from one location to another unassisted.

## Project Details

* Given a budget of $50, we had to create a sweater that detects objects in front or on the sides of a person. 

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
