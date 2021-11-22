#define forward 5
#define backward 4
#define right 2
#define left 3

void setup() {
  //control pins
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);

}

void loop() {
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);

}
