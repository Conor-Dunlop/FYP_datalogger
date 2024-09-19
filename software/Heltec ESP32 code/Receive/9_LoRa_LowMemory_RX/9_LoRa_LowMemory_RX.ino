/*******************************************************************************************************
  Programs for Arduino - Copyright of the author Stuart Robinson - 08/02/20

  This program is supplied as is, it is up to the user of the program to decide if the program is
  suitable for the intended purpose and free from errors.
*******************************************************************************************************/

/*******************************************************************************************************
  Program Operation - The program receives a packet without using a processor buffer, the LoRa device
  internal buffer is read direct and copied to variables. The program is a simulation of the type of packet
  that might be received from a GPS tracker. Note that in this example a buffer of text is part of the
  received packet, this does need a processor buffer which is filled with data from the LoRa device internal
  buffer, if you don't need to send and receive text then the uint8_t receivebuffer[32]; definition can be
  ommited.

  The contents of the packet received, and printed to serial monitor, should be;

  "Tracker1" (buffer)      - trackerID
  1+             (uint32_t)    - packet count
  51.23456       (g:\DownloadsG\SX12XX-LoRa-master.zipfloat)       - latitude
  -3.12345       (float)       - longitude
  199            (uint16_t)    - altitude
  8              (uint8_t)     - number of satellites
  3999           (uint16_t)    - battery voltage
  -9             (int8_t)      - temperature

  Serial monitor baud rate is set at 9600.

*******************************************************************************************************/

#include <SPI.h>
#include <SX126XLT.h>
#include "Settings.h"
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>
#include <stdio.h>
#include <fmt.h>

SX126XLT LT;


uint32_t RXpacketCount;
uint16_t errors;

uint8_t RXPacketL;               //length of received packet
int8_t  PacketRSSI;              //RSSI of received packet
int8_t  PacketSNR;               //signal to noise ratio of received packet
String result = "";
char receivedBuffer[255];  // Buffer to store the received string

const char* ssid = "Galaxy";
const char* password = "yoyoyoyo";
const char* ntpServer = "pool.ntp.org";
// Define NTP Client to get time


String serverName = "https://dataloggerapi.azurewebsites.net/logData";
// String headerPacket = "{\"loggerID\":\"Wifi_testing\",\"sensorID\":\"ALL\",\"timestamp\":\"2024-09-18T02:56:57.336Z\",\"data\":\"";
// "loggerID\":\"Wifi_testing\",\"sensorID\":\"ALL\",\"timestamp\":\"2024-09-18T02:56:57.336Z\",\"data\":
// "loggerID":"Wifi_testing","sensorID":"ALL","timestamp":"2024-09-19T02:04:20Z,"data":"


String headerStart = "{\"loggerID\":\"Wifi_testing\",\"sensorID\":\"ALL\",\"timestamp\":\"";
// String headerMiddle = "2024-09-18T02:56:57.336Z\"
String headerEnd = "\",\"data\":\"";

uint16_t led_status;

// Variable to save current epoch time
unsigned long epochTime; 

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

String printNowUsingCLibrary(time_t now) {
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  int year = timeinfo.tm_year + 1900; // tm_year starts in year 1900 (!)
  int month = timeinfo.tm_mon + 1; // tm_mon starts at 0 (!)
  int day = timeinfo.tm_mday; // tm_mday starts at 1 though (!)
  int hour = timeinfo.tm_hour;
  int mins = timeinfo.tm_min;
  int sec = timeinfo.tm_sec;
  int day_of_week = timeinfo.tm_wday; // tm_wday starts with Sunday=0

  char datebuffer[100];
  sprintf(datebuffer, "%04d-%02d-%02dT%02d:%02d:%02dZ",
            year, month, day, hour, mins, sec);
            
  // return fmt::format::sprintf("%04d-%02d-%02dT%02d:%02d:%02dZ",
  //         year, month, day, hour, mins, sec);

  return String(datebuffer);


  // string date_time = ("%04d-%02d-%02dT%02d:%02d:%02dZ",
  //     year, month, day, hour, mins, sec, dow_string);
  // Serial.println(date_time);    
  // Serial.println(F(" (C lib)"));


}

void loop()
{
  epochTime = getTime();

  String currenttime = printNowUsingCLibrary(epochTime);
  Serial.print(currenttime);
  String headerMiddle = currenttime;


  String headerPacket = headerStart + headerMiddle + headerEnd;

  // Serial.print(headerPacket);
  // Serial.print("Epoch Time: ");
  // Serial.print(hour(epochTime));
  // Serial.print(month());
  // Serial.println(epochTime);

  // digitalWrite(LED?_PIN, HIGH);
  // Serial.println("trying to turn LED on ");  
  RXPacketL = LT.receiveSXBuffer(0, 0, WAIT_RX);       //returns 0 if packet error of some sort, no timeout

  // digitalWrite(LED1, HIGH);      //something has happened
  // button_pressed();
  PacketRSSI = LT.readPacketRSSI();
  PacketSNR = LT.readPacketSNR();

  if (RXPacketL == 0)
  {
    packet_is_Error();
  }
  else
  {
    packet_is_OK();
  }

  // String result = MySerial.readStringUntil('\n'); 

  // Serial.println(result);
  result = String(receivedBuffer);
  result.replace("\n", "");
  result.replace("\r", "");
  result.replace("\"", "'");
  Serial.println(WiFi.status() == WL_CONNECTED);
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;

    String serverPath = serverName;
    Serial.println(serverPath);
    http.begin(serverName);
    http.addHeader("Host", "dataloggerapi.azurewebsites.net");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("accept", "*/*");

    
    int httpCode = http.POST(headerPacket + String(result) + String("\",\"dataType\": \"string\"}"));

    String resultInfo;
    if (httpCode > 0) {
        Serial.println(http.getString());
        resultInfo = "Success, HTTP Response Code: " + (String)httpCode;
    } else {
        resultInfo = "Error, HTTP Response Code: " + (String)httpCode;
    }

    http.end();
    Serial.println(resultInfo);
    Serial.print("Sent ");
    Serial.println(headerPacket + String(result) + String("\",\"dataType\": \"string\"}"));
    
  

  }


  delay(100);


}


uint8_t packet_is_OK()
{

  //packet has been received, now read from the SX12xx Buffer using the same variable type and
  //order as the transmit side used.

  RXpacketCount++;
  Serial.print(RXpacketCount);
  Serial.print(F("  "));

  LT.startReadSXBuffer(0);               //start buffer read at location 0

  LT.readBufferChar(receivedBuffer);  // Read the string data from the SX buffer
  
  RXPacketL = LT.endReadSXBuffer();  // End the buffer read

  Serial.print(F("Received: "));
  Serial.println(receivedBuffer);  // Print the received string

  return RXPacketL;
}


void packet_is_Error()
{
  uint16_t IRQStatus;
  IRQStatus = LT.readIrqStatus();

  if (IRQStatus & IRQ_RX_TIMEOUT)
  {
    Serial.print(F("RXTimeout"));
  }
  else
  {
    errors++;
    Serial.print(F("PacketError"));
    printpacketDetails();
    Serial.print(F("IRQreg,"));
    Serial.print(IRQStatus, HEX);
  }
}


void printpacketDetails()
{
  Serial.print(F("  RSSI,"));
  Serial.print(PacketRSSI);
  Serial.print(F("dBm,SNR,"));
  Serial.print(PacketSNR);
  Serial.print(F("dB"));
}


void led_Flash(uint16_t flashes, uint16_t delaymS)
{
  uint16_t index;

  for (index = 1; index <= flashes; index++)
  {
    digitalWrite(LED1, HIGH);
    delay(delaymS);
    digitalWrite(LED1, LOW);
    delay(delaymS);
  }
}


void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  configTime(43200, 46400, ntpServer);
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");



  pinMode(LED1, OUTPUT);
  // pinMode(LED_PIN, OUTPUT);
  led_Flash(2, 125);



  SPI.begin();

  if (LT.begin(NSS, NRESET, RFBUSY, DIO1, SW, LORA_DEVICE))
  {
    led_Flash(2, 125);
  }
  else
  {
    Serial.println(F("Device error"));
    while (1)
    {
      led_Flash(50, 50);                                            //long fast speed flash indicates device error
    }
  }

  LT.setupLoRa(Frequency, Offset, SpreadingFactor, Bandwidth, CodeRate, Optimisation);

  Serial.println(F("Receiver ready"));
  Serial.println();
}