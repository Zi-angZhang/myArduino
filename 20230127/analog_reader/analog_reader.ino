/*
    AnalogReadSerial
    Reads an analog input on pin a0, prints the result to the serial monitor
*/

void setup() {
    // initialize the serial communication at 9600 bits per second
    Serial.begin(9600);
}

void loop() {
    // the loop routine runs over and over again forever
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    delay(9600); // delay in between reads for stability
}
