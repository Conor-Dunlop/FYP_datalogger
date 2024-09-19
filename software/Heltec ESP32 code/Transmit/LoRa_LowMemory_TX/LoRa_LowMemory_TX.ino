/*******************************************************************************************************
  Programs for Arduino - Copyright of the author Stuart Robinson - 08/02/20

  This program is supplied as is, it is up to the user of the program to decide if the program is
  suitable for the intended purpose and free from errors.
*******************************************************************************************************/

/*******************************************************************************************************
  Program Operation - The program transmits a packet without using a processor buffer, the LoRa device
  internal buffer is filled direct with variables. The program is a simulation of the type of packet
  that might be sent from a GPS tracker. Note that in this example a buffer of text is part of the
  transmitted packet, this does need a processor buffer which is used to fill the LoRa device internal
  buffer, if you don't need to transmit text then the uint8_t trackerID[] = "Tracker1"; definition
  can be ommited.

  The matching receiving program '9_LoRa_LowMemory_RX' can be used to receive and display the packet,
  though the program  '15_LoRa_RX_Structure' should receive it as well, since the packet contents are
  the same.

  The contents of the packet received, and printed to serial monitor, should be;
  
  "tracker1" (buffer)      - trackerID 
  1+             (uint32_t)    - packet count    
  51.23456       (float)       - latitude   
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
#include <HardwareSerial.h>

// #define BUTTON_PIN 34

HardwareSerial MySerial(1); // define a Serial for UART1
const int MySerialRX = 19;
const int MySerialTX = 20;
int count = 0;
// struct Data {
//   // uint8_t buff[];  
//   int8_t led_status;
// } data_t;

// char led_status;
// uint16_t led_status;



SX126XLT LT;

uint32_t TXpacketCount = 0;
uint8_t TXPacketL;
uint32_t startmS, endmS;
String result = "";

// void button_pressed()
// {

//   if (digitalRead(BUTTON_PIN) == HIGH) {
//       led_status = 1;
//     }
//     else {
//       led_status = 0;
//     }

// }



void loop()
{
  TXpacketCount++;
  // button_pressed();
  // if (Send_Test_Packet())
  // {




  Serial.print(TXpacketCount);
  Serial.print(F(" "));
  Serial.print(TXPacketL);
  Serial.print(F(" Bytes Sent"));
  Serial.print(F(" "));
  Serial.print(endmS - startmS);    Serial.print(F("mS"));
  Send_Test_Packet();
  delay(500);
  // Serial.println("LED status is");
  // Serial.print(led_status);
  // }
  // else
  // {
  //   Serial.print(F("Send Error - IRQreg,"));
  //   Serial.print(LT.readIrqStatus(), HEX);
  // }

  Serial.println();
  delay(packet_delay);
}


uint8_t Send_Test_Packet()
{
  //The SX12XX buffer is filled with variables of a known type and order. Make sure the receiver
  //uses the same variable type and order to read variables out of the receive buffer.
  uint8_t len;
  result = "";
  
  while(MySerial.available() > 0){
    result = MySerial.readStringUntil('\n'); 
  }
  Serial.print(result);
  delay(100);

  LT.startWriteSXBuffer(0);                         //start the write at location 0
  // LT.writeChar(led_status);
  // LT.writeUint16(led_status);
  LT.writeBufferChar(&result[0], result.length());


  len = LT.endWriteSXBuffer();

  digitalWrite(LED1, HIGH);
  startmS = millis();



  TXPacketL = LT.transmitSXBuffer(0, len, 5000, TXpower, WAIT_TX);   //set a TX timeout of 5000mS

  endmS = millis();

  digitalWrite(LED1, LOW);

  return TXPacketL;
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

  // pinMode(BUTTON_PIN, INPUT);
  led_Flash(2, 125);

  Serial.begin(9600);
  MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);

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

  Serial.println(F("Transmitter ready"));
  Serial.println();
}