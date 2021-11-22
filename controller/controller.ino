
int incomingByte;
const int buttonPin1 = 12;
const int buttonPin2 = 13;
const int buttonPin3 = 7;
const int buttonPin4 = 8;
int right = 0;
int left = 0;
int pres = 0;
int psave = 0;
int rs = 0;
int en = 0;
unsigned long time;
    
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
}

void loop() {
  psave=pres;
  
  left = digitalRead(buttonPin1);
  right = digitalRead(buttonPin2);
  rs = digitalRead(buttonPin4);
  en = digitalRead(buttonPin3);
  
  if (left==right){
    pres = 0;
  }
  else if (left==1){
    pres = 2;
  }
  else if (right==1){
    pres = 1;
  }
  if (rs==1){
    pres = 3;
  }
  if (en==1){
    pres = 4;
  }
  Serial.println(pres);
    
  delay(60);
}
