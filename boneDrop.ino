
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <SoftwareSerial.h>

//uncomment for debug mode
//#define debug

// constants won't change. They're used here to set pin numbers:
//const int buttonPin = 12;     // the number of the pushbutton pin
//int buttonState = 0;         // variable for reading the pushbutton status
//int lastState;
int posState;


//forum Code snippet #1
// this constant won't change:
const int  buttonPin = 3;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
volatile int buttonState = 0;
//boolean buttonState = 0;         // current state of the button....voltaile int in example.
boolean lastButtonState = 0;     // previous state of the button
boolean stateOfLift;             //woohoo another state var
//forum Code snippet #1




// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 50
//#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 7
#define STEP 6

//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

void setup() {

  // initialize the pushbutton pin as an input:
  //pinMode(buttonPin, INPUT_PULLUP);

  //forum Code snippet #1
#ifdef debug
  Serial.println("SETUP");
#endif

  // initialize the button pin as a input with internal pullup enabled
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  //forum Code snippet #1
  attachInterrupt(1, pin_ISR, LOW);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);

   pinMode(LED_BUILTIN, OUTPUT);


}

void loop() {

#ifdef debug
  //Serial.print("hey-0 debug mode active");
#endif
  // energize coils - the motor will hold position
  //stepper.enable();//turn this on evertyime

//Tom 
 
/*
  static unsigned long last_loop_time = 0;
  unsigned long loop_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (loop - last_loop_time > 100) 
 {
   
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  stepper.move(1000);
  
 }
 digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
 // enable interrupts
    
 int buttonState = digitalRead(buttonPin);
  // print out the state of the button:
 Serial.println(buttonState);

 last_loop_time = loop_time;
 */
 
}



/*
 * innerrupt, service interrupt, do stuff, return interrupts
 */
void pin_ISR() {

  volatile static unsigned long last_interrupt_time = 0;
  volatile unsigned long interrupt_time = millis();
  volatile uint8_t SaveSREG;
  
  SaveSREG = SREG;
  cli();   // disable interrupts//

  
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if (interrupt_time - last_interrupt_time > 200) 
 {
  //doItToIt

 
  
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  stepper.move(1);
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
 
  
  //Serial.println("Valid Input");
   
 }
  last_interrupt_time = interrupt_time;
  sei();   // enable interrupts

  
 //sei();   // enable interrupts
} 
