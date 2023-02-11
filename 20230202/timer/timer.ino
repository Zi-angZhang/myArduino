#include <Servo.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <TimeLib.h>
#include <SPI.h>

#define SERVO_PIN 3
#define MAX_DEVICES 4 // number of led display
#define CS_PIN 10
#define SWITCH_PIN 7 
#define SWITCH_DEGREE 18
//#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define HARDWARE_TYPE MD_MAX72XX::DR1CR1RR0_HW
//https://majicdesigns.github.io/MD_MAX72XX/class_m_d___m_a_x72_x_x.html
#define LAMP_MODULE false
#define DISPLAY_MODULE true
#define SWITCH_MODULE true
#define TOMATO_WORK 25 //minutes
#define TOMATO_REST 5 //minutes

// fonts: https://github.com/MajicDesigns/MD_MAX72XX/blob/main/Font%20Builder/sys_var_single.txt
Servo lamp; // servo controller (multiple can exist)

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
int pos = 3;    // servo starting position
String msgStr = "\x010 \x00a"; // display message before receiving msg from PC
bool lastStatus = false; // button status
bool working = false; // timer status
unsigned long workStart = 0; // work start time
unsigned long workingZone = TOMATO_WORK * 60000; // working time in ms
unsigned long relaxingZone = TOMATO_REST * 60000; //resting time in ms
unsigned long tomatoPeriod = workingZone + relaxingZone; // one period in ms

void setup() {
  if (LAMP_MODULE){lamp.attach(SERVO_PIN); } // start servo control
  lamp.write(-10);
  delay(2000);

  if (DISPLAY_MODULE) {
    Serial.begin(9600);
    //setSyncProvider(requestSync);
    myDisplay.begin();
    myDisplay.setIntensity(0);
    myDisplay.setInvert(true);
    //myDisplay.setTextAlignment(PA_CENTER);
    myDisplay.setTextAlignment(PA_RIGHT);
    myDisplay.setZoneEffect(0, true, PA_FLIP_LR);
  }
  delay(1000);
  //lamp.write(13);

}

void loop() {
  if (SWITCH_MODULE) {
    if (digitalRead(SWITCH_PIN) == LOW) {
      myDisplay.setTextAlignment(PA_CENTER);
      myDisplay.print("off");
      // button is released
      if (lastStatus) { lamp.write(0); lastStatus = false; }
    }
    else {
      myDisplay.setTextAlignment(PA_RIGHT);
      pomodoroTimer();// myDisplay.print("on");
      // button is pressed
      lamp.write(SWITCH_DEGREE);
      if (not lastStatus) { 
        lamp.write(SWITCH_DEGREE); 
        lastStatus = true; 
        workStart = millis();
      }
    }
  }
}
void pomodoroTimer() {
  unsigned long currentTime = (millis() - workStart) % tomatoPeriod;
  if (currentTime > workingZone){
    int secDisplay = ((tomatoPeriod - currentTime) % 60000)/1000;
    int minDisplay = (tomatoPeriod - currentTime) / 60000;
    myDisplay.print("r"+String(minDisplay)+":"+String(secDisplay));
  } else {
    int secDisplay = ((workingZone - currentTime) % 60000)/1000;
    int minDisplay = (workingZone -currentTime) / 60000;
    myDisplay.print("\x002 \x00e "+String(minDisplay));
  }
}

  //if (DISPLAY_MODULE) {
  //  myDisplay.setTextAlignment(PA_CENTER);
  //  myDisplay.print(msgStr);
  //  if (Serial.available()) {
  //    msgStr = Serial.readString();
  //    msgStr.trim();
  //    Serial.print(msgStr);
  //  }
  //}
  //if (LAMP_MODULE) {
  //  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //    // in steps of 1 degree
  //    lamp.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15); // delay to allow the servo to reach the desired position
  //    if (pos==90){
  //      delay(5000); //wait 5 seconds once positioned at 90 degrees
  //    }
  //  }
  //  delay(5000); // wait 5 seconds after reaching 180 degrees
 
  //  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //    lamp.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(15);
  //    if (pos==90){
  //      delay(5000); // wait 5 seconds once positioned at 90 degrees
  //    }
  //  }
  //  delay(5000); // wait 5 seconds after arriving back at 0 degrees
  //}
  //}
