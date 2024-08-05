#include <Arduino.h>
#include <HardwareSerial.h>

#include <WiFi.h>
#include <HTTPClient.h>


// const char* ssid = "REPLACE_WITH_YOUR_SSID";
// const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// this is the ip and port for the test server
String serverName = "http://10.0.0.43:8008/";

HardwareSerial MySerial(2); // define a Serial for UART2
const int MySerialRX = 16;
const int MySerialTX = 17;
int count = 0;

String headerPacket = "{loggerID:\"Wifi_testing\",timestamp:\"None\",location:\"\",sensors:";

void setup() {
  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);

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
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName;
      Serial.println(serverPath);
      http.begin(serverName);
      http.addHeader("Host", "10.0.0.43");
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
    Serial.print(result);
  }
  delay(100);
}