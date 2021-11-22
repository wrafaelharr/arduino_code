#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

#define drive_bourd 3

int right_sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  //initalize sensor
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
}

void loop() {
 if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  right_sensor = map(sensor.readRangeContinuousMillimeters(), 0, 1300, 0, 250);
  
  Serial.println(right_sensor);

}
