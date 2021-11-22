#include <Wire.h>
#include <VL53L0X.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

VL53L0X sensor;
RF24 radio(9, 10); // CE, CSN

#define f 6
#define b 5
#define l 8
#define r 7
#define bourd2 3

const byte addresses [][6] = {"00001", "00002"}; 
int speeds = 255;
int comb;
int up;
int down;
int right;
int left;
int vrx;
int vry;
int buttonState;
boolean self_driving = false;
boolean rc_car = true;

void setup() {
  //begin wire communication
  Serial.begin(9600);
  Wire.begin();
  
  //initalize sensor
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();
  
  //initalize radio
  radio.begin();          
  radio.openWritingPipe(addresses[1]);  
  radio.openReadingPipe(1, addresses[0]); 
  radio.setPALevel(RF24_PA_MIN);  
  
  //set pinmodes
  pinMode(f, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(bourd2, INPUT);
}

void loop() { 
  //read radio data
  radio.startListening();
  radio.read(&comb, sizeof(comb));

  //interpret radio
  buttonState = comb%10;
  vrx = comb/100;
  vry = (comb/10)%10;
  
  //stop if disconected
  if(radio.available()){
  //map to ups and downs
  if (vrx < 5){
     up = map(vrx, 5, 0, 0, 255);
     down = 0;
  }
  else if (vrx > 5){
    up = 0;
    down = map(vrx, 5, 10, 0, 255);
  }
  else{
    up = 0;
    down = 0;
  }

  //map to lefts and rights
  if (vry < 1){
    right = true;
    left = false;
  }
  else if (vry > 1){
    right = false;
    left = true;
  }
  else{
    right = false;
    left = false;
  }
  }
  //stop if disconected
  else{
    up = 0;
    down = 0;
    right = false;
    left = false;
    
    //initalize radio
    radio.begin();          
    radio.openWritingPipe(addresses[1]);  
    radio.openReadingPipe(1, addresses[0]); 
    radio.setPALevel(RF24_PA_MIN); 
  }
  
  analogWrite(f, up);
  analogWrite(b, down);
  digitalWrite(l, left);
  digitalWrite(r, right);
  
  delay(10);
}
