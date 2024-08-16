#include <Arduino.h>
#include <HardwareSerial.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include "secrets.h"

const char* ssid = SSID;
const char* password = PASSWORD;

// this is the ip and port for the test server
//String serverName = "http://10.0.0.43:8008/";
String serverName = "https://dataloggerapi.azurewebsites.net/logData";

HardwareSerial MySerial(2); // define a Serial for UART2
const int MySerialRX = 16;
const int MySerialTX = 17;
int count = 0;

String headerPacket = "{loggerID:\"Wifi_testing\",timestamp:\"None\",location:\"\",sensors:";

void scanNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("SSID List:");
  Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") Network: ");
    Serial.println(WiFi.SSID(thisNet));
  }
}
 

void setup() {
  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);

  scanNetworks();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  // Serial.printf("Received %d:", count++);
  while(MySerial.available() > 0){
    String result = MySerial.readStringUntil('\n'); 
    result.replace("\n", "");
    result.replace("\r", "");
    Serial.println(result);
    Serial.println(WiFi.status() == WL_CONNECTED);
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName;
      Serial.println(serverPath);
      http.begin(serverName);
      http.addHeader("Host", "dataloggerapi.azurewebsites.net");
      http.addHeader("Content-Type", "application/json");
      http.addHeader("accept", "*/*");

      
      int httpCode = http.POST(headerPacket + String(result) + String("}"));
      String resultInfo;
      if (httpCode > 0) {
          Serial.println(http.getString());
          resultInfo = "Success, HTTP Response Code: " + (String)httpCode;
      } else {
          resultInfo = "Error, HTTP Response Code: " + (String)httpCode;
      }

      http.end();
      Serial.println(resultInfo);
    }
    //Serial.print(result);
  }
  delay(100);
}

int main() {
  setup();
  loop();
  return 1;
}