#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <TimeLib.h>
// https://github.com/ivankravets/MD_MAX72XX/blob/master/src/MD_MAX72xx_lib.h
#include <SPI.h>
 

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

// https://how2electronics.com/8x32-max7219-dot-matrix-led-display-with-arduino/
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
//#define HARDWARE_TYPE MD_MAX72XX::OTHER_HW
//#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
// parola_HW
 
#define MAX_DEVICES 4
#define CS_PIN 10
 
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
 
String msgStr = "waiting";

void setup() {
  Serial.begin(9600);
  //setSyncProvider(requestSync);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setInvert(true);
  delay(2000);
}
 
void loop() {
    // for scroll text
    //if (myDisplay.displayAnimate()) {
    //  myDisplay.displayText(msgStr.c_str(), PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    //  if (Serial.available()) {
    //    //processSyncMessage();
    //    msgStr = Serial.readString();
    //    msgStr.trim();
    //    Serial.print(msgStr);
    //  }
    //}
	myDisplay.setTextAlignment(PA_CENTER);
    myDisplay.print(msgStr);
    if (Serial.available()) {
      //processSyncMessage();
      msgStr = Serial.readString();
      msgStr.trim();
      Serial.print(msgStr);
    }
    //myDisplay.displayText("test", PA_CENTER, PA_SCROLL_LEFT, 200);
	//myDisplay.setTextAlignment(PA_LEFT);
	//myDisplay.print("Left");
	//delay(2000);
	//
	//myDisplay.setTextAlignment(PA_CENTER);
	//myDisplay.print("Center");
	//delay(2000);

	//myDisplay.setTextAlignment(PA_RIGHT);
	//myDisplay.print("Right");
	//delay(2000);

	//myDisplay.setTextAlignment(PA_CENTER);
	//myDisplay.print("Invert");
	//delay(2000);

	//myDisplay.setInvert(false);
	//myDisplay.print(1234);
	//delay(2000);

} 

void processSyncMessage() {
    String incomingByte = Serial.readString();
    const char * msgChar = incomingByte.c_str();
    
    while (myDisplay.displayAnimate()) {
      myDisplay.displayText(msgChar, PA_CENTER, 100, 100, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }
}
//void processSyncMessage() {
//  unsigned long pctime;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
//
//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
//       setTime(pctime); // Sync Arduino clock to the time received on the serial port
//       digitalClockDisplay();  
//     }
//  }
//}
//
//
//void digitalClockDisplay(){
//  // digital clock display of the time
//  myDisplay.setTextAlignment(PA_CENTER);
//  myDisplay.print(hour());
//  delay(2000);
//}
//time_t requestSync()
//{
//  Serial.write(TIME_REQUEST);  
//  return 0; // the time will be sent later in response to serial mesg
//}
