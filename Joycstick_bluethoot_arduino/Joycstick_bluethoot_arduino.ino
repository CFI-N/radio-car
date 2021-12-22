#include <SoftwareSerial.h>

char message;

SoftwareSerial bluetooth(10, 11); // (RX, TX) (pin Rx BT, pin Tx BT)
unsigned long previousMillis = 0;        // will store last time LED was updated
int ledState = LOW;
const int ledPin =  LED_BUILTIN;
int JoyStick_X = A0; // Signal de l'axe X
int JoyStick_Y = A1; // Signal de l'axe Y
int Button = 3; // Bouton
// constants won't change:
const long interval = 1000;
int previous_X;
int previous_Y;
int previous_B;
String data;
unsigned int x, y, b;
int btn_status;
const int Joystick_Interval = 5;
const int interval_Emission = 200;
unsigned long previousTime = 0;



void setup()
{
  // Ouvre la voie série avec l'ordinateur
  Serial.begin(38400);
  // Ouvre la voie série avec le module BT
  bluetooth.begin(38400);
  pinMode(ledPin, OUTPUT);
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (Button, INPUT);
  x = analogRead (JoyStick_X) ;
  y = analogRead (JoyStick_Y) ;

  // Lorsqu'on pousse sur le bouton, la mise à la masse
  // active la résistance de PullUp.
  digitalWrite(Button, HIGH);

  Serial.begin (38400); // Sortie série à 9600 bauds
  bluetooth.println(x);
  bluetooth.println(y);

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
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);

  }


  //Les valeurs sont lues, sont converties en tension...
  x = analogRead (JoyStick_X) ;
  y = analogRead (JoyStick_Y) ;
  btn_status = digitalRead (Button);

  if (btn_status == 1)
  {
    b = 0;
  }
  else
  {
    b = 1;
  }

  if ( previous_X != x) {
    if (previous_X > x) {
      if ((previous_X - x) < Joystick_Interval) {
        // pass
      } else {
        data = data + x + "X" ;
      }
    } else {
      if ((x - previous_X) < Joystick_Interval) {
        // pass
      } else {
        data = data + x + "X" ;
      }
    }
  } else {
    data = data + "";
  }

  if ( previous_Y != y) {
    if (previous_Y > y) {
      if ((previous_Y - y) < Joystick_Interval) {
        // pass
      } else {
        data = data + y + "Y" ;
      }
    } else {
      if ((y - previous_Y) < Joystick_Interval) {
        // pass
      } else {
        data = data + y + "Y" ;
      }
    }
  } else {
    data = data + "";
  }



  if ( previous_B != b || currentMillis - previousTime >= interval_Emission) {
    data = data + b + "B";
  } else {
    data = data + "";
  }

  if ( data != "") {
    previousTime = currentMillis;
    bluetooth.println(data);
  }

  previous_X = x;
  previous_Y = y;
  previous_B = b;
  data = "";
}
