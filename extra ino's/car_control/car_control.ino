
#define forward 5
#define backward 4
#define right 2
#define left 3

int vry = A0;
int vrx = A1;
int xaxis = 0;
int yaxis = 0;

void setup() {
  Serial.begin(9600);

  //joy stick pins
  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);

  //control pins
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  xaxis = analogRead(vrx);
  yaxis = analogRead(vry);

  if (xaxis < 500){
    digitalWrite(forward, HIGH);
    digitalWrite(backward, LOW);
  }
  else if (xaxis > 540){
    digitalWrite(backward, HIGH);
    digitalWrite(forward, LOW);
  }
  else{
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
  }

  if (yaxis < 500){
    digitalWrite(left, LOW);
    digitalWrite(right, HIGH); 
  }
  else if (yaxis > 540){
    digitalWrite(left, HIGH);
    digitalWrite(right, LOW);
  }
  else{
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
  }
}
