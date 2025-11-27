#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEClient.h>
#include <BLE2902.h>

#define THRESHOLD 100
#define EMG_PIN 0
#define N 16

// Adresse MAC (voir la doc BLE ESP32 pour l'utilisation)
static BLEAddress robotAddress("24:EC:4A:CE:3F:D6");
static BLEUUID serviceUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID charUUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");

BLEClient* pClient;
BLERemoteCharacteristic* pRemoteCharacteristic;

int buffer[N];
int idx = 0;
int prevVal = 0;

void setup() {
  Serial.begin(115200);
  for(int i=0; i<N; i++) buffer[i]=0;
    // Initialisation BLE en "Client"
  BLEDevice::init("");
  pClient = BLEDevice::createClient();
  bool connected = pClient->connect(robotAddress);
  if(connected) {
    pRemoteCharacteristic = pClient->getService(serviceUUID)->getCharacteristic(charUUID);
    Serial.println("Connecté au robot !");
  }
}

void loop() {
  int val = analogRead(EMG_PIN);
  int filtered = val - prevVal;
  prevVal = val;
  int envelope = abs(filtered); // ou filtered*filtered
  buffer[idx] = envelope;
  idx = (idx + 1) % N;
  long sum = 0;
  for(int i=0; i<N; i++) sum += buffer[i];
  int smoothEnvelope = sum / N;
  //Serial.print(val); Serial.print(",");
  //Serial.print(filtered); Serial.print(",");

  if (smoothEnvelope > THRESHOLD) {
    // Ici tu déclenches le robot
    // digitalWrite(moteurPin, HIGH);
    pRemoteCharacteristic->writeValue("F"); // envoie avance robot
    Serial.println("Contraction! Commande envoyée");
  }
  Serial.println(smoothEnvelope);
  delay(30);
}