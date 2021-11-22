#include <Wire.h>
#include <VL53L0X.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define SERVO_PIN 3
#define XSHUT1 7
#define XSHUT2 8

VL53L0X sensor1;
VL53L0X sensor2;

Servo Servo1; //create a servo object

int servoAngle = 0;
int count = 0;
long reset_time = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  pinMode(XSHUT1, INPUT);
  pinMode(XSHUT1, INPUT);

  digitalWrite(XSHUT1, LOW);
  digitalWrite(XSHUT1, LOW);
  delay(10);

  digitalWrite(XSHUT1, HIGH);

  sensor1.begin(0x30);
  
  digitalWrite(XSHUT2, HIGH);

  //sensor2.begin(0x29);
  
  sensor1.init();
  sensor1.setTimeout(500);
  sensor1.startContinuous();
  Servo1.attach(SERVO_PIN);
}

void loop() {
  Serial.println(sensor1.readRangeContinuousMillimeters());
  delay(5);

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
