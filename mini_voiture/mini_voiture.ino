int Motor_Left_UP = 6;
int Motor_Left_DOWN = 7;
int Motor_Right_UP = 5;
int Motor_Right_DOWN = 4;

void setup() {
  pinMode(Motor_Left_UP, OUTPUT);
  pinMode(Motor_Left_DOWN, OUTPUT);
  pinMode(Motor_Right_UP, OUTPUT);
  pinMode(Motor_Right_DOWN, OUTPUT);
}

void loop() {
  // Avance simple
  digitalWrite(Motor_Left_UP, LOW);
  digitalWrite(Motor_Left_DOWN, HIGH);
  digitalWrite(Motor_Right_UP, LOW);
  digitalWrite(Motor_Right_DOWN, HIGH);
  delay(2000);

  // Stop
  digitalWrite(Motor_Left_UP, LOW);
  digitalWrite(Motor_Left_DOWN, LOW);
  digitalWrite(Motor_Right_UP, LOW);
  digitalWrite(Motor_Right_DOWN, LOW);
  delay(2000);
}
