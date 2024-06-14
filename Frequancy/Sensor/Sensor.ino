// pins
int sensorPin = A0; 

// values
int sensorValue = 0;  
int prevSenseVal = 0;
int index = 0;

// averager
int numSamples = 500;
int SenseVals[500];

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin)-23;

  // sample
  SenseVals[index] = sensorValue; //abs(sensorValue - prevSenseVal);

  // average samples
  float avg = 0;
  for (int i=0; i < numSamples; i++) {
    avg += SenseVals[i];
  }
  avg /= numSamples;
   
  // print value
  Serial.println(avg);

  // record previous value
  prevSenseVal = sensorValue;

  // increase index
  index += 1;

  // delay
  delay(1);
}