#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define vrx A1
#define vry A0

RF24 radio(9, 10); // CE, CSN

const byte addresses [][6] = {"00001", "00002"};
int xaxis;
int yaxis;
int dist;
int dist2;

void setup() {
  pinMode(vrx, INPUT);

  Serial.begin(9600);
  
  radio.begin();                            //Starting the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.

}

void loop() {
  xaxis = analogRead(vrx);

  delay(5);
  radio.startListening();                    //This sets the module as receiver
  if (radio.available()){
    radio.read(&dist, sizeof(dist));
  }

  Serial.println(dist);
}
