#define LED_PIN 8
#define BUTTON_PIN 7

void setup() {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == HIGH) {
        delay(1000);
        digitalWrite(LED_PIN, LOW);
    }
    else {
        delay(1000);
        digitalWrite(LED_PIN, HIGH);
    }
}
