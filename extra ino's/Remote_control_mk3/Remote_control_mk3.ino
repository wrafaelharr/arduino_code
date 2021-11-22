#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int vry = A0;
int vrx = A1;
int xaxis = 0;
int yaxis = 0;
int comb;
int up;
int down;
int left;
int right;
int x;
int y;
int buttonPin = 2;
int buttonState = 0;

RF24 radio(9, 10); // CE, CSN         

const byte addresses [][6] = {"00001", "00002"};  

void setup() {
  Serial.begin(9600);
  
  radio.begin();                            
  radio.openWritingPipe(addresses[1]);      
  radio.openReadingPipe(1, addresses[0]);   
  radio.setPALevel(RF24_PA_MIN);  

  pinMode(vrx, INPUT);
  pinMode(vrx, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  xaxis = analogRead(vrx);
  yaxis = analogRead(vry); 
  buttonState = digitalRead(buttonPin);

  x = map(xaxis, 0, 1040, 0, 10);
  y = map(yaxis, 0, 1040, 0, 3);

  comb = x*100+y*10+buttonState;

  
  radio.stopListening();
  radio.write(&comb, sizeof(comb));

  Serial.println(comb);
  delay(2);
}
