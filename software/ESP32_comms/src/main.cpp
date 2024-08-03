#include <Arduino.h>
#include <HardwareSerial.h>


HardwareSerial MySerial(2); // define a Serial for UART2
const int MySerialRX = 16;
const int MySerialTX = 17;
int count = 0;

void setup() {
  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);
}

void loop() {
  // Serial.printf("Received %d:", count++);
  // if any strange fromating happens its because you are using windows
  while(MySerial.available() > 0){
    String result = MySerial.readStringUntil('\r'); 
    Serial.print(result);
  }
  delay(100);
}