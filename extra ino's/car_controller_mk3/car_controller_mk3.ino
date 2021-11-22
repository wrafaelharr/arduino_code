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
int angle;
int comb;

void setup() {
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  
  Serial.begin(9600);
  
  radio.begin();                            //Starting the radio communication
  radio.openWritingPipe(addresses[0]);      //Setting the address at which we will send the data
  radio.openReadingPipe(1, addresses[1]);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);            //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
}

void loop() {
  xaxis = analogRead(vrx);

  radio.startListening();                    //This sets the module as receiver
  if (radio.available()){
    radio.read(&comb, sizeof(comb));
  }

  if (comb > 9999){
    dist = comb % 100;
    dist2 = (comb / 100) % 100;
  }
  else if (comb > 0) {
    angle = comb % 1000;
  }
  /*
  radio.stopListening();                           //This sets the module as transmitter
  radio.write(&xaxis, sizeof(xaxis));   //Sending the data
  */
  Serial.println(angle);
}
