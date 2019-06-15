
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
  attachInterrupt(1, pin_ISR, CHANGE);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);


}

void loop() {

#ifdef debug
  //Serial.print("hey-0 debug mode active");
#endif
  // energize coils - the motor will hold position
  stepper.enable();//turn this on evertyime
 /* // read the state of the pushbutton value:
  //buttonState = digitalRead(buttonPin); //NATE put in state change detection
  //if (buttonState != lastState) {   //check state if different
  //stepper.move(posState);
  //stepper.disable();
  //delay(200);
  //forum Code Snippet #1
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState)
  {
#ifdef debug
    Serial.println("if (buttonState != lastButtonState)");
#endif
    if (buttonState == LOW)
    {
#ifdef debug
      Serial.println("buttonState == LOW && if (buttonState != lastButtonState)");
#endif
      // if the current state is LOW then the button
      // went from off to on:

      //nate 2019_0613 do motor stuff

      //stepper.rotate(360); //spin that mother, use degree notation. whatever

      //Tom motor Stuff start //
#ifdef debug
      Serial.println("tomMotorStuff && buttonState == LOW && if (buttonState != lastButtonState)");
#endif
      //stepper.move(-MOTOR_STEPS*MICROSTEPS); //make motor go back 360 degrees by microsteps


      if (posState == 200) posState = -200;
      else posState = 200;
      //Tom motor stuff end
    }
    Serial.println("button pressed Dude");
#ifdef debug
    Serial.println("buttonPressed && buttonState == LOW && if (buttonState != lastButtonState)");
#endif
    digitalWrite(ledPin, !digitalRead(ledPin)); // toggle the output
  }
  delay(500);
  lastButtonState = buttonState;*/
}
// save the current state as the last state,
//for next time through the loop
//
//forum Code Snippet #1






void pin_ISR() {

  //don't call Serial as re-entrance problems
  //#ifdef debug
  Serial.println("in Interrupt");
  //#endif
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
  //check state
  //stateofLift = -1;                        //this might be too much ish for an interrupt
  //stepper.rotate(360);
  //stepper.move(1000);
}
