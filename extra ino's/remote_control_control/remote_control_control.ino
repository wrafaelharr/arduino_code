
#define forward 2
#define backward 3
#define right 4
#define left 5

void setup() {
  Serial.begin(9600);
  
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

}

void loop() {     
  //digitalWrite(backward, LOW);
  //digitalWrite(forward, HIGH);
  Serial.println(1); 
  delay(1000);
  digitalWrite(forward, LOW);
  //digitalWrite(backward, HIGH); 
  Serial.println(0);
  delay(1000);
}
