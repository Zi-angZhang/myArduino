#include <Servo.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <TimeLib.h>
#include <SPI.h>

#define SERVO_PIN 3
#define MAX_DEVICES 4 // number of led display
#define CS_PIN 10
#define SWITCH_PIN 7 
#define SWITCH_DEGREE 14
//#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define HARDWARE_TYPE MD_MAX72XX::DR1CR1RR0_HW
//https://majicdesigns.github.io/MD_MAX72XX/class_m_d___m_a_x72_x_x.html
#define LAMP_MODULE true
#define DISPLAY_MODULE false
#define SWITCH_MODULE true

Servo lamp; // servo controller (multiple can exist)

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
int pos = 0;    // servo starting position
String msgStr = "\x010 \x00a"; // display message before receiving msg from PC
bool lastStatus = false; // off, default

void setup() {
  //if (LAMP_MODULE){lamp.attach(SERVO_PIN); } // start servo control

  //lamp.write(13);

}

void loop() {
    while (true) {
lamp.write(pos);
delay(20);
pos += 1;
}
}
