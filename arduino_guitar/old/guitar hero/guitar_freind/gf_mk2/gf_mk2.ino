#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//VERIABLES
int dist = 0;
int prev_dist = 0;
int dif = 0;

void setup() {
  Serial.begin(115200);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  //find dist
  prev_dist = dist;
  dist = measure.RangeMilliMeter;

  //find difference
  dif = abs(dist-prev_dist);
  if (dif > 100){
    dif = 100;
  }

  // send signal
  Serial.println(dif);
    
  delay(10);
}
