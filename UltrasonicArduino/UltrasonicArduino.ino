 // HC-SR04 ultrasonic rangefinder demo
// Popular code uses pulseIn to measure echo pulse, pulseIn is a blocking function
// Using interrupts for reading the incoming pulse is better approach because it won't stall your main program
// You are welcome to use this code for the project
// You might need to do additional calibration and data filtering
// Note sources of innacuracies of some components like micros(). It has a small error, check online why this happens

// Pinout:
// VCC (5VDC)
// GND (return)
// TRIG (trigger input)mnbvcdxv
// ECHO (echo output)

// For sensor operation refer to datasheet:
// https://www.mouser.com/ds/2/813/HCSR04-1022824.pdf


#define TRIGF PD2  // trigger pin front ultrasonic
#define ECHOF PD4  // echo output front ultrasonic
#define TRIGR PC2  // trigger pin right ultrasonic
#define ECHOR PC3  // echo output right ultrasonic
#define TRIGL PB4  // trigger pin left ultrasonic
#define ECHOL PB5  // echo pin left ultrasonic

#define BUZZERF PB2 // front buzzer output ultrasonic 
#define BUZZERL PB3 // sides buzzer output ultrasonic 
#define BUZZERR PD3

// riseTime and fallTime will be modified by interrupt so we need to declare them as volatile
volatile unsigned long riseTime1;  // timestamp when echo signal goes high
volatile unsigned long riseTime2;  // timestamp when echo signal goes high
volatile unsigned long riseTime3;  // timestamp when echo signal goes high

volatile unsigned long fallTime1;  // timestamp when echo signal goes low
volatile unsigned long fallTime2;  // timestamp when echo signal goes low
volatile unsigned long fallTime3;  // timestamp when echo signal goes low

unsigned long pulseTime1;          // difference between riseTime and fallTime
unsigned long pulseTime2;          // difference between riseTime and fallTime
unsigned long pulseTime3;          // difference between riseTime and fallTime

unsigned long distance1; // our range
unsigned long distance2; // our range
unsigned long distance3; // our range

float getdistance1();
float getdistance2();
float getdistance3();

void frontRangeDetector();
void leftRangeDetector();
void rightRangeDetector();
/***************************************************************************************************************************************************/
void setup()
{
  Serial.begin(9600);

  //Front Buzzer Mode
  // using timer 1 because timer 0 is used for delay functions
  TCCR1A = 0x23; // setting channel b to clear on compare match (10), setting the rightmost waveform generation bits to 11 to count Fast PWM
  TCCR1B = 0x12; // setting the leftmost waveform generation bit to 1 to make TOP OCROA and a prescalar of 8
  OCR1A = 255; // to get a 4kHz signal 
  OCR1B = 150;

  TCCR2A = 0xA1; // setting channel b to clear on compare match (10), setting the rightmost waveform generation bits to 11 to count Fast PWM
  TCCR2B = 0x02; // setting the leftmost waveform generation bit to 1 to make TOP OCROA and a prescalar of 8
  OCR2A = 250;
  OCR2B = 200;
  
  DDRD = 0x04;
  DDRC = 0x04;
  DDRB = 0x10;

  // Setting up pin change interrupt for echo (PD3), PCINT19
  PCICR = 0x07;
  PCMSK0 = (1 << PCINT5);
  PCMSK1 = (1 << PCINT11);
  PCMSK2 = (1<<PCINT20);  // only enabling PCINT19  
}

void loop() 
{
  float front_range1 = getdistance1();
  float front_range2 = getdistance2();
  float front_range3 = getdistance3();
  cli();
  if ((front_range1 < front_range2) && (front_range1 < front_range3))
    frontRangeDetector(front_range1); // call function to buzz on ranges
  else if ((front_range2 < front_range1) && (front_range2 < front_range3))
    rightRangeDetector(front_range2);
  else if ((front_range3 < front_range1) && (front_range3 < front_range2))
    leftRangeDetector(front_range3);
  sei();
  Serial.print(front_range1);
  Serial.print(" ");
  Serial.print(front_range2);
  Serial.print(" ");
  Serial.println(front_range3);
}

// function to calculate the distance
float getdistance1()
{
  // clear trig pin
  PORTD &= ~(1<<TRIGF);
  delayMicroseconds(2);
  
  // send out 10 us pulse
  PORTD |= (1<<TRIGF); //added or
  delayMicroseconds(10);
  PORTD &= ~(1<<TRIGF);
  // sound travels at 343 m/s which is 0.0343 cm/us
  // distance = time*velocity
  // we need to divide result by 2 because sound travels 
  // to object and back so the incoming pulse is twice longer
  distance1 = (pulseTime1*0.0343/2); // result in cm 
  return distance1 / 30.48;
}

float getdistance2()
{
  // clear trig pin
  PORTC &= ~(1<<TRIGR);
  delayMicroseconds(2);
  
  // send out 10 us pulse
  PORTC |= (1<<TRIGR); //added or
  delayMicroseconds(10);
  PORTC &= ~(1<<TRIGR);
  // sound travels at 343 m/s which is 0.0343 cm/us
  // distance = time*velocity
  // we need to divide result by 2 because sound travels 
  // to object and back so the incoming pulse is twice longer
  distance2 = (pulseTime2*0.0343/2); // result in cm 
  return distance2 / 30.48;
}

float getdistance3()
{
  // clear trig pin
  PORTB &= ~(1<<TRIGL);
  delayMicroseconds(2);
  
  // send out 10 us pulse
  PORTB |= (1<<TRIGL); //added or
  delayMicroseconds(10);
  PORTB &= ~(1<<TRIGL);
  // sound travels at 343 m/s which is 0.0343 cm/us
  // distance = time*velocity
  // we need to divide result by 2 because sound travels 
  // to object and back so the incoming pulse is twice longer
  distance3 = (pulseTime3*0.0343/2); // result in cm 
  return distance3 / 30.48;
}


// Interrupt service vector for pin change:
// ISR (PCINT0_vect) pin change interrupt for D8 to D13
// ISR (PCINT1_vect) pin change interrupt for A0 to A5
// ISR (PCINT2_vect) pin change interrupt for D0 to D7
// We need PCINT2_vect because we are using PD3 as input (echo)
ISR(PCINT2_vect)
{  

/* This is the working code here */
  if((PIND & (1<<ECHOF)) == (1<<ECHOF)){
    riseTime1 = micros();
  }
  else{
      // measure the time when echo pin goes low
      fallTime1 = micros();
      pulseTime1 = fallTime1 - riseTime1; // this is our echo pulse, its length is proportional to the measured distance
    }
}
ISR(PCINT1_vect)
{  

/* This is the working code here */
  if((PINC & (1<<ECHOR)) == (1<<ECHOR)){
    riseTime2 = micros();
  }
  else{
      // measure the time when echo pin goes low
      fallTime2 = micros();
      pulseTime2 = fallTime2 - riseTime2; // this is our echo pulse, its length is proportional to the measured distance
    }
}
ISR(PCINT0_vect)
{  

/* This is the working code here */
  if((PINB & (1<<ECHOL)) == (1<<ECHOL)){
    riseTime3 = micros();
  }
  else{
      // measure the time when echo pin goes low
      fallTime3 = micros();
      pulseTime3 = fallTime3 - riseTime3; // this is our echo pulse, its length is proportional to the measured distance
    }
}
void frontRangeDetector(float range)
{
  // buzzing on the front buzzer
  if (range <= 1) {
    DDRB |=_BV(BUZZERF);
    //delay(7500);
  }
  else if (range <= 1.5) {
    DDRB |=_BV(BUZZERF);
    delay(5000);
    DDRB &= ~(1<<BUZZERF);
    delay(5000);
  }
  else if (range <= 2.3) {
    DDRB |=_BV(BUZZERF);
    delay(12500);
    DDRB &= ~(1<<BUZZERF);
    delay(12500);
  }
  else if (range <= 3.1) {
    DDRB |=_BV(BUZZERF);
    delay(25000);
    DDRB &= ~(1<<BUZZERF);
    delay(25000);
  }
  else if(range <=5){
    DDRB |=_BV(BUZZERF);
    delay(32000);
    DDRB &= ~(1<<BUZZERF);
    delay(32000);
  }
  else if (range >= 5) {
    DDRB &= ~(1<<BUZZERF);
    //delay(7500);
  }

  
} // end frontRangeDetector

void leftRangeDetector(float range)
{
  // buzzing the buzzer on the left
  if (range <= 1) {
    DDRB |=_BV(BUZZERL);
    //delay(7500);
  }
  else if (range <= 1.5) {
    DDRB |=_BV(BUZZERL);
    delay(5000);
    DDRB &= ~(1<<BUZZERL);
    delay(5000);
  }
  else if (range <= 2.3) {
    DDRB |=_BV(BUZZERL);
    delay(12500);
    DDRB &= ~(1<<BUZZERL);
    delay(12500);
  }
  else if (range <= 3.1) {
    DDRB |=_BV(BUZZERL);
    delay(25000);
    DDRB &= ~(1<<BUZZERL);
    delay(25000);
  }
  else if(range <=5){
    DDRB |=_BV(BUZZERL);
    delay(32000);
    DDRB &= ~(1<<BUZZERL);
    delay(32000);
  }
  else if (range >= 5) {
    DDRB &= ~(1<<BUZZERL);
    //delay(7500);
  }
}
void rightRangeDetector(float range)
{
  // buzzing the buzzer on the right
  if (range <= 1) {
    DDRD |=_BV(BUZZERR);
    //delay(7500);
  }
  else if (range <= 1.5) {
    DDRD |=_BV(BUZZERR);
    delay(5000);
    DDRD &= ~(1<<BUZZERR);
    delay(5000);
  }
  else if (range <= 2.3) {
    DDRD |=_BV(BUZZERR);
    delay(12500);
    DDRD &= ~(1<<BUZZERR);
    delay(12500);
  }
  else if (range <= 3.1) {
    DDRD |=_BV(BUZZERR);
    delay(25000);
    DDRD &= ~(1<<BUZZERR);
    delay(25000);
  }
  else if(range <=5){
    DDRD |=_BV(BUZZERR);
    delay(32000);
    DDRD &= ~(1<<BUZZERR);
    delay(32000);
  }
  else if (range >= 5) {
    DDRD &= ~(1<<BUZZERR);
    //delay(7500);
  }
}
