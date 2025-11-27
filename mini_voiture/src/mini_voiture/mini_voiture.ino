#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

int Motor_Left_UP = 6;    // D4
int Motor_Left_DOWN = 7;  // D5
int Motor_Right_UP = 5;   // D3
int Motor_Right_DOWN = 4; // D2

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

String command = ""; // Arduino String

#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

void handleCommand(char cmd);

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("✅ Appareil connecté");
  }
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("❌ Appareil déconnecté");
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    command = pCharacteristic->getValue(); 
    if (command.length() > 0) {
      Serial.print("Commande reçue: ");
      Serial.println(command);
      handleCommand(command[0]); // on ne prend que le 1er caractère
    }
  }
};

void setup() {
  Serial.begin(115200);

  pinMode(Motor_Left_UP, OUTPUT);
  pinMode(Motor_Left_DOWN, OUTPUT);
  pinMode(Motor_Right_UP, OUTPUT);
  pinMode(Motor_Right_DOWN, OUTPUT);

  BLEDevice::init("MiniRobot");  // Nom visible sur ton téléphone
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("🤖 MiniRobot prêt, connecte-toi en BLE !");
}

void handleCommand(char cmd) {
  Serial.print("Action: ");
  Serial.println(cmd);

  if (cmd == 'F') { // Forward
  // Avance
  digitalWrite(Motor_Left_UP, LOW);
  digitalWrite(Motor_Left_DOWN, HIGH);
  digitalWrite(Motor_Right_UP, LOW);
  digitalWrite(Motor_Right_DOWN, HIGH);

  // Temps pour avancer ~5 cm 
  delay(600);

  // Stop automatique
  digitalWrite(Motor_Left_UP, LOW);
  digitalWrite(Motor_Left_DOWN, LOW);
  digitalWrite(Motor_Right_UP, LOW);
  digitalWrite(Motor_Right_DOWN, LOW);
  }
  
  else if (cmd == 'B') { // Backward
    digitalWrite(Motor_Left_UP, HIGH);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, HIGH);
    digitalWrite(Motor_Right_DOWN, LOW);

    // Temps pour avancer ~5 cm (a ajuster)
    delay(600); 

    // Stop automatique
    digitalWrite(Motor_Left_UP, LOW);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, LOW);
    digitalWrite(Motor_Right_DOWN, LOW);
  }
  else if (cmd == 'L') { // Left
    digitalWrite(Motor_Left_UP, HIGH);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, LOW);
    digitalWrite(Motor_Right_DOWN, HIGH);

    // Temps pour avancer ~5 cm (a ajuster)
    delay(600); 

    // Stop automatique
    digitalWrite(Motor_Left_UP, LOW);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, LOW);
    digitalWrite(Motor_Right_DOWN, LOW);
  }
  else if (cmd == 'R') { // Right
    digitalWrite(Motor_Left_UP, LOW);
    digitalWrite(Motor_Left_DOWN, HIGH);
    digitalWrite(Motor_Right_UP, HIGH);
    digitalWrite(Motor_Right_DOWN, LOW);

    // Temps pour avancer ~5 cm (a ajuster)
    delay(600);

    // Stop automatique
    digitalWrite(Motor_Left_UP, LOW);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, LOW);
    digitalWrite(Motor_Right_DOWN, LOW);
  }
  else if (cmd == 'S') { // Stop
    digitalWrite(Motor_Left_UP, LOW);
    digitalWrite(Motor_Left_DOWN, LOW);
    digitalWrite(Motor_Right_UP, LOW);
    digitalWrite(Motor_Right_DOWN, LOW);
  }
}

void loop() {
  delay(100);
}
