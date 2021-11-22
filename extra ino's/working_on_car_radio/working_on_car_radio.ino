#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define forward 5
#define backward 4
#define right 2
#define left 3

int vry = A0;
int vrx = A1;
int xaxis = 0;
int yaxis = 0;

RF24 radio(9, 10); // CE, CSN 
        
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = A0;
boolean button_state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button_pin, INPUT);

  //joy stick pins
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop(){
  // read the value from the sensor:
  xaxis = analogRead(vrx);
  yaxis = analogRead(vry);

  button_state = analogRead(button_pin);
  Serial.println(xaxis);
  
  if(button_state == HIGH){
    const char text[] = analogRead(vry);
    radio.write(&text, sizeof(text));                  //Sending the message to receiver
  }
  
  else{
    const char text[] = "Your Button State is LOW";
    radio.write(&text, sizeof(text));                  //Sending the message to receiver 
  }
  
  radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
  delay(100);
}
