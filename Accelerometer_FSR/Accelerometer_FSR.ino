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

#define LEFTVIB PB4
#define RIGHTVIB PB5

volatile bool vibrate;
volatile float vibrate_length;

volatile bool timeToTurn;
volatile int timeToTurn_length = 3000;

volatile bool above = false;
volatile bool below = true;

void setup(void) 
{
  // for pin change interrupts
  //PCICR = 0x06;
  PCICR = 0x02;
  PCMSK1 = 0x08;
  //PCMSK2 = 0x04;

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
  if(vibrate == true){
    //cli(); 
    delay(vibrate_length);
    PORTB = ~((1 << LEFTVIB) | (1 << RIGHTVIB)); // turn off vibration
    vibrate = false;
    //sei(); might want to disable interrupts while clicked, discuss with Adam.
  }
  if(timeToTurn){
    delay(timeToTurn_length);
    PORTB = ~((1 << LEFTVIB) | (1 << RIGHTVIB)); // turn off vibration
    timeToTurn = false;
  }
  
}

ISR(PCINT1_vect){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) 
  {
    if((PINC & 0x08) == 0x08){
      sei();  // allow interrupts so mag can run the heading function
      sensors_event_t event; 
      mag.getEvent(&event);
      cli();
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

//ISR(PCINT2_vect){
//  cli();
//  static volatile unsigned long last_interrupt_time2 = 0;
//  unsigned long interrupt_time2 = millis();
//  if (interrupt_time2 - last_interrupt_time2 > 200) 
// {
//   if((PIND & 0x04) == 0x04){
//    count += 1;
//    //flag = true;
//    Serial.print("Step Count ");
//    Serial.println(count);
//  }
// }
// last_interrupt_time2 = interrupt_time2;
// sei();
//}

ISR(ADC_vect){
  cli();
  val = *squeeze_data >> 6;
////  if(val > 100){
////  Serial.println(val);
////  }
//  if(val > 300 && last_val < 500){
//    Serial.println(val);
//    Serial.println("last_val");
//    Serial.println(last_val);
//    count +=1;
//    int numberOfSteps = 1;
//    if(count == numberOfSteps){
//      PORTB = (1 << RIGHTVIB) | (1 << LEFTVIB);
//      timeToTurn = true;
//    }
//    Serial.print("Step Count: ");
//    Serial.println(count);
//  }
//  last_val = val;

  val = *squeeze_data >> 6;
  if(val > 250){
    above = true;
  }
  else{
    above = false;
  }
  if(val < 200){
    below = true;
  }
  if(above == true && below == true){
    count +=1;
    int numberOfSteps = 1;
    if(count == numberOfSteps){
      PORTB = (1 << RIGHTVIB) | (1 << LEFTVIB);
      timeToTurn = true;
    }
    Serial.print("Step Count: ");
    Serial.println(count);
    below = false;
  }
  sei();
}
