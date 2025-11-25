#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEClient.h>
#include <BLE2902.h>

#define THRESHOLD 150
#define EMG_PIN 0

// Adresse MAC (voir la doc BLE ESP32 pour l'utilisation)
static BLEAddress robotAddress("24:EC:4A:CE:3F:D6");
static BLEUUID serviceUUID("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID charUUID("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");

BLEClient* pClient;
BLERemoteCharacteristic* pRemoteCharacteristic;

int prevVal = 0;
int window[10];
int idx = 0;

void setup() {
  Serial.begin(115200);
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
  int val = analogRead(0);
  int filtered = val - prevVal; // filtre passe-haut très simple
  // Détection de bosse :
  if (filtered > THRESHOLD) {
    // Ici tu déclenches le robot
    // digitalWrite(moteurPin, HIGH);
    pRemoteCharacteristic->writeValue("F"); // envoie avance robot
    Serial.println("Contraction! Commande envoyée");
  }
  prevVal = val;
  Serial.println(filtered);
  delay(100);
}