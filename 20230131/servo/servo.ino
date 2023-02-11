#include <Servo.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <TimeLib.h>
#include <SPI.h>

#define SERVO_PIN 3
#define MAX_DEVICES 4 // number of led display
#define CS_PIN 10
#define SWITCH_PIN 7 
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define LAMP_MODULE true
#define DISPLAY_MODULE true
#define SWITCH_MODULE true

Servo lamp; // servo controller (multiple can exist)

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int pos = 0;    // servo starting position
String msgStr = "\x010 \x00a"; // display message before receiving msg from PC
bool lastStatus = false; // off, default

void setup() {
  if (LAMP_MODULE){lamp.attach(SERVO_PIN); } // start servo control
  lamp.write(0);
  delay(2000);

  if (DISPLAY_MODULE) {
    Serial.begin(9600);
    //setSyncProvider(requestSync);
    myDisplay.begin();
    myDisplay.setIntensity(0);
    myDisplay.setInvert(true);
    myDisplay.setTextAlignment(PA_CENTER);
  }
  delay(1000);
  //lamp.write(13);

}

void loop() {
  if (SWITCH_MODULE) {
    if (digitalRead(SWITCH_PIN) == LOW) {
      myDisplay.print("off");
      if (lastStatus) { lamp.write(0); lastStatus = false; }
    }
    else {
      myDisplay.print("on");
      lamp.write(13);
      if (not lastStatus) { lamp.write(13); lastStatus = true; }

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
}
