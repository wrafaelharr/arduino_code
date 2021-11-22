#include <Servo.h>
#define SERVO_PIN 3

Servo Servo1; //create a servo object

int servoAngle = 0;
int count = 0;
long reset_time = 0;


void setup() {
  Serial.begin(9600);
  Servo1.attach(SERVO_PIN);  //attach the pin to the object so that we can send the signal to it
  reset_time = millis();
}

void loop() {
  if (millis() - reset_time > 800*3){
    reset_time = millis();
  }
  else if (millis() - reset_time > 905*2){
    Servo1.write(0);
    Serial.println(millis());
  }
  else if (millis() - reset_time > 615){
    Servo1.write(250);
    Serial.println(millis());
  }
}
