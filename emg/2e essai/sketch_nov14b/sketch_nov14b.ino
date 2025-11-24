int prevVal = 0;
#define THRESHOLD 150

void setup() { Serial.begin(115200); }
void loop() {
  int val = analogRead(0);
  int filtered = val - prevVal; // filtre passe-haut très simple
  // Détection de bosse :
  if (filtered > THRESHOLD) {
    // Ici tu déclenches le robot
    // digitalWrite(moteurPin, HIGH);
    Serial.println("Contraction détectée !");
  }
  prevVal = val;
  Serial.println(filtered);
  delay(100);
}

