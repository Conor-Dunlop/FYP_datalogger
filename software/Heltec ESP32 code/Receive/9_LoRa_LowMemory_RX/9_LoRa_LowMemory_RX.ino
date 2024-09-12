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

// #define LED_PIN 7

SX126XLT LT;

uint32_t RXpacketCount;
uint16_t errors;

uint8_t RXPacketL;               //length of received packet
int8_t  PacketRSSI;              //RSSI of received packet
int8_t  PacketSNR;               //signal to noise ratio of received packet
String result = "";

// struct Data {
//   // uint8_t buff[];  
//   int8_t led_status;
// } data_t;
uint16_t led_status;

// void button_pressed()
// {
//   if (led_status == 1) {
//     digitalWrite(LED_PIN, HIGH);
//     // Serial.println("bruh bruh");
//   }
//   else {
//     // led_status = off
//     digitalWrite(LED_PIN, LOW);
//     // Serial.println("else workin?");
//   }

// }




void loop()
{
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

  // digitalWrite(LED1, LOW);
  // Serial.println("led status is ");
  // Serial.print(led_status);
}


uint8_t packet_is_OK()
{

  //packet has been received, now read from the SX12xx Buffer using the same variable type and
  //order as the transmit side used.

  RXpacketCount++;
  Serial.print(RXpacketCount);
  Serial.print(F("  "));

  LT.startReadSXBuffer(0);               //start buffer read at location 0

  char receivedBuffer[255];  // Buffer to store the received string
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
  pinMode(LED1, OUTPUT);
  // pinMode(LED_PIN, OUTPUT);
  led_Flash(2, 125);

  Serial.begin(9600);

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



