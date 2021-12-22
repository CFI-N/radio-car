#include <SoftwareSerial.h>

char message;

SoftwareSerial bluetooth(10, 11); // (RX, TX) (pin Rx BT, pin Tx BT)
const int ledPin =  LED_BUILTIN;// the number of the LED pin

int ledState = LOW;             // ledState used to set the LED

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 150;  

void setup()
{
    // Ouvre la voie série avec l'ordinateur
    Serial.begin(38400);
    // Ouvre la voie série avec le module BT
    bluetooth.begin(38400);
    pinMode(ledPin, OUTPUT);
}

void loop() // run over and over
{
    if (bluetooth.available()) {
  message = bluetooth.read();
        Serial.print(message);
    }
    if (Serial.available()) {
  message = Serial.read();
  bluetooth.print(message);
  Serial.print(message);
    }
}
