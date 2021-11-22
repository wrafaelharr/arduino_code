#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte addresses [][6] = {"00001", "00002"};  //Setting the two addresses. One for transmitting and one for receiving
int sensor2_pin = 6;
int servo_ang_pin = 5;
int dist2;
int xaxis;

void setup() {
  radio.begin();                           //Starting the radio communication
  radio.openWritingPipe(addresses[1]);     //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[0]);  //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver. 

  //declare pinmodes
  pinMode(sensor2_pin, INPUT);
  pinMode(servo_ang_pin, INPUT);
}

void loop() {  
 //read bourd 2
  int dist2 = pulseIn(sensor2_pin, HIGH, 4200);
  if (dist2 == 0 && digitalRead(sensor2_pin) == 1) {
      dist2 = 2100;
  }
  
  int angle = pulseIn(servo_ang_pin, HIGH, 4200);
  if (angle == 0 && digitalRead(servo_ang_pin) == 1) {
      angle = 2100;
  }

  dist2 = 19999;
  delay(5);
  radio.stopListening();                             //This sets the module as transmitter
  radio.write(&dist2, sizeof(dist2));  //Sending the data
  delay(5);
  
  radio.startListening();                            //This sets the module as receiver
  while(!radio.available());                         //Looking for incoming data
  radio.read(&xaxis, sizeof(xaxis)); //Reading the data

  Serial.println(dist2);
}
