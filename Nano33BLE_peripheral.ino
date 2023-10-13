/*
  This program uses the ArduinoBLE library to set up an Arduino Nano 33 BLE 
  as a peripheral device and specifies a service and a characteristic.

  The circuit:
  - Arduino Nano 33 BLE. 

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
      
const char* deviceServiceUuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
const char* deviceServiceCharacteristicUuid = "beb5483e-36e1-4688-b7f5-ea07361b26a8";

BLEService ourService(deviceServiceUuid); 
BLEByteCharacteristic ourCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  while (!Serial);  
  
  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(ourService);
  ourService.addCharacteristic(ourCharacteristic);
  BLE.addService(ourService);
  ourCharacteristic.writeValue(-1);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");
}

void loop() {
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to the central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      int charac = 1;
      Serial.print("* Writing value to our characteristic: ");
      Serial.println(charac);
      ourCharacteristic.writeValue((byte)charac);
      Serial.println("* Writing value to our characteristic done!");
      Serial.println(" ");
    }
  
  }
    
  Serial.println("* Disconnected from the central device!");
}
