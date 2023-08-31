// pins
int sensorPin = A0; 

// values
int sensorValue = 0;  
int prevSenseVal = 0;
int index = 0;

// averager
int numSamples = 200;
int SenseVals[200];

void setup() {
  Serial.begin(115200);
  while (!Serial) {;}
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // sample
  SenseVals[index] = sensorValue;

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
}