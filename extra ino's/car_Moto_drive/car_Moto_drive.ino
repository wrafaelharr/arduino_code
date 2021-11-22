#define right 2
#define left 3
#define backward 4
#define forward 5

void setup() {
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(forward, OUTPUT);

}

void loop() {
  digitalWrite(forward, LOW);
  delay(1000);
  digitalWrite(forward, LOW);
  delay(1000);

}
