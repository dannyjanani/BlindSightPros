#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
 
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

volatile int count = 0;
//unsigned char * squeeze_data = 0x79;
unsigned short * squeeze_data = 0x78;
unsigned short last_val = 0;
unsigned short val;

#define LEFTVIB PB4  // left vibrator
#define RIGHTVIB PB5  // right vibrator

volatile bool vibrate;  // bool to vibrate for compass reading
volatile float vibrate_length;  // how long to vibrate for

volatile bool timeToTurn; // bool to vibrate for step counting
volatile int timeToTurn_length = 3000;  // vibrate for 3 seconds

volatile bool above = false;  // top threshold for force senstive resistor analog reading
volatile bool below = false;   // bottom threshold for force senstive resistor analog reading

void setup(void) 
{
  // for pin change interrupts
  PCICR = 0x04;  // turn on ISR for PCINT2
  PCMSK2 = 0x04;  // pin 2

  // for analog conversion
  //ADCSRA = 0xEC;
  ADCSRA = 0xED;
  ADCSRB = 0x00;
  ADMUX = 0x60;

  // turn pin 12 and 13 as output in DDRB:
  DDRB = (1 << LEFTVIB) | (1 << RIGHTVIB);
  
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  mag.begin();
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM3/03 detected ... Check your wiring!");
    while(1);
  }
}
 
void loop(void) 
{
  //PCMSK1 = 0x08;  // pin A3
  PCMSK2 = 0x04;
  if(vibrate == true){ // vibrate for compass heading
    //cli(); 
    delay(vibrate_length);
    PORTB = ~((1 << LEFTVIB) | (1 << RIGHTVIB)); // turn off vibration
    vibrate = false;
    //sei(); might want to disable interrupts while clicked, discuss with Adam.
  }
  if(timeToTurn){  // vibrate for number of steps
    delay(timeToTurn_length);
    PORTB = ~((1 << LEFTVIB) | (1 << RIGHTVIB)); // turn off vibration
    timeToTurn = false;
  }
  
}

ISR(PCINT2_vect){
  // timer is to debounce button
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) 
  {
    if((PIND & 0x04) == 0x04){
      sei();  // allow interrupts so mag can run the heading function
      sensors_event_t event; 
      mag.getEvent(&event);
      cli(); // turn off interrupts
      float Pi = 3.14159;
      
      // Calculate the angle of the vector y,x
      float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
      
      // Normalize to 0-360
      if (heading < 0)
      {
        heading = 360 + heading;
      }
      
      int scalar = 2;
      int degreeLeniency = 10;
      int rel_degrees;
      if(heading > 0 && heading <= 180){
        PORTB = (1 << LEFTVIB);
        rel_degrees= (int) abs(heading - 0); // relative degrees
        vibrate_length = ceil((rel_degrees / 180.0) * scalar * 100);
      }
      else{
        PORTB = (1 << RIGHTVIB);
        rel_degrees= (int) abs(heading - 180); // relative degrees
        vibrate_length = ceil((1 -(rel_degrees / 180.0)) * scalar * 100);
      }
      // delay for length of vibrate, then turn off? Must be done in the loop so that we can use delay
      vibrate = true;
      //vibrate_length = ceil((1 -(rel_degrees / 180.0)) * scalar * 100);
      
      Serial.print("Compass Heading: ");
      Serial.println(heading);
      Serial.println(rel_degrees);
      Serial.println(vibrate_length);
    }
  }
  last_interrupt_time = interrupt_time;
}
ISR(ADC_vect){
  cli();
  val = *squeeze_data >> 6;
  if(val > 300){  // pass top threshold 
    above = true;
  }
  else{
    above = false; // didnt pass top threshold 
  }
  if(val < 50){
    below = true; // came from below the bottom threshold
  }
  if(above == true && below == true){
    count +=1;
    int numberOfStepsHallway = 9;
    int numberOfStepsCafe = 49;
    if(count == numberOfStepsHallway || count == numberOfStepsCafe){
      PORTB = (1 << RIGHTVIB) | (1 << LEFTVIB);
      timeToTurn = true;
    }
    Serial.print("Step Count: ");
    Serial.println(count);
    below = false;
  }
  sei();
}
