/*
  Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
  Ported to Arduino ESP32 by Evandro Copercini
  updated by chegewara and MoThunderz
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ESP32Servo.h>

#include "bitmap.hpp"
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic_2 = NULL;
BLECharacteristic* pCharacteristic_3 = NULL;
BLECharacteristic* pCharacteristic_4 = NULL;
BLEDescriptor *pDescr;
BLE2902 *pBLE2902;

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;
int face = 1;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR1_UUID          "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR2_UUID          "e3223119-9445-4e96-a4a1-85358c4046a2"
#define CHAR3_UUID          "4e854d58-2ca4-448d-b1cb-6481e19567e8"
#define CHAR4_UUID          "6c6dc165-eb19-41dd-85d0-7cd7d2b64394"

#define SERVO_PIN1 21 // ESP32 pin GPIO26 connected to servo motor
#define SERVO_PIN2 20 // ESP32 pin GPIO26 connected to servo motor
Servo servoMotor1;
Servo servoMotor2;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class CharacteristicCallBack: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) override { 
    String value_string = pChar->getValue();
    int value_int = value_string.toInt();
    
    // Identify which characteristic was written to
    String charName = "Unknown";
    
    if (pChar == pCharacteristic_2) {
      charName = "Characteristic 2";
      servoMotor1.write(90 + value_int) ;

    } else if (pChar == pCharacteristic_3) {
      charName = "Characteristic 3";
      servoMotor2.write(90 + value_int) ;
      
    } else if (pChar == pCharacteristic_4) {
      charName = "Characteristic 4";
      face = value_int;
      Serial.println(face);
    }

    Serial.println(charName + " written with value: " + String(value_int));
    
  }
};

void setup() {
  Serial.begin(115200);

  u8g2.begin();
  u8g2.enableUTF8Print(); //nécessaire pour écrire des caractères accentués
  u8g2.setColorIndex(0);

  servoMotor1.attach(SERVO_PIN1);
  servoMotor2.attach(SERVO_PIN2);
  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHAR1_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );                   

  pCharacteristic_2 = pService->createCharacteristic(
                      CHAR2_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  
                    );  

  pCharacteristic_3 = pService->createCharacteristic(
                      CHAR3_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  
                    );  

  pCharacteristic_4 = pService->createCharacteristic(
                      CHAR4_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  
                    );

  // Create a BLE Descriptor
  
  pDescr = new BLEDescriptor((uint16_t)0x2901);
  pDescr->setValue("A very interesting variable");
  pCharacteristic->addDescriptor(pDescr);
  
  pBLE2902 = new BLE2902();
  pBLE2902->setNotifications(true);
  
  // Add all Descriptors here
  pCharacteristic->addDescriptor(pBLE2902);
  pCharacteristic_2->addDescriptor(new BLE2902());
  pCharacteristic_3->addDescriptor(new BLE2902());
  pCharacteristic_4->addDescriptor(new BLE2902());

  // After defining the desriptors, set the callback functions
  pCharacteristic_2->setCallbacks(new CharacteristicCallBack());
  pCharacteristic_3->setCallbacks(new CharacteristicCallBack());
  pCharacteristic_4->setCallbacks(new CharacteristicCallBack());
  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  
  // notify changed value
  if (deviceConnected) {
      pCharacteristic->setValue(value);
      pCharacteristic->notify();
      value++;
      delay(1000);
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
  }
  
  if ()
    if (face == 0){
      u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
      u8g2.drawXBMP( 0, 0, 128, 64, fuck_face); // position, largeur, hauteur
      u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
    } else if (face == 1){
      u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
      u8g2.drawXBMP( 0, 0, 128, 64, default_face); // position, largeur, hauteur
      u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
    } else if (face == 2){
      u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
      u8g2.drawXBMP( 0, 0, 128, 64, angy_face); // position, largeur, hauteur
      u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
    } else if (face == 3){
      u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
      u8g2.drawXBMP( 0, 0, 128, 64, sleep_face); // position, largeur, hauteur
      u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
    }

}
