#include "Timer.h"

Timer t;

int pump1Event;
int pump2Event;
int pump3Event;

boolean priorityPump1 = false;
boolean priorityPump2 = false;
boolean priorityPump3 = false;
/**
   Copyright (c) 2009 Andrew Rapp. All rights reserved.

   This file is part of XBee-Arduino.

   XBee-Arduino is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   XBee-Arduino is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with XBee-Arduino.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <XBee.h>

#define PUMP1 A0
#define PUMP2 A1
#define PUMP3 A2

#define PLANT1 "01916206589221"
#define PLANT2 "01916206589227"
#define PLANT3 "01916206589216"
#define OVERWRITE 10


/*
  This example is for Series 2 XBee
  Receives a ZB RX packet and sets a PWM value based on packet data.
  Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();


void setup()
{
  // start serial
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  xbee.begin(Serial);

}


String printFrame(ZBRxResponse rx1) {
  String x = "";
  for (int i = 0; i < rx1.getDataLength(); i++)
  {
    if (i >= 0 && i <= 7)
    {
      x += rx1.getData(i);
    }
    Serial.print("byte [");
    Serial.print(i, DEC);
    Serial.print("] is ");
    Serial.println(rx1.getData(i), HEX);
  }
  return x;
}


void performPumpingAction(String x) {

  if (x == PLANT1)
  {
    if (rx.getData(8) == 1)
    {
      Serial.println("Pump1 will turn on");
      analogWrite(PUMP1, 1023);
      delay(100);
    }
    else
    {
      Serial.println("Pump1 will turn off");
      analogWrite(PUMP1, 0);
      delay(100);
    }
  }
  else if (x == PLANT2)
  {
    if (rx.getData(8) == 1)
    {
      Serial.println("Pump2 will turn on");
      analogWrite(PUMP2, 1023);
      delay(100);
    }
    else
    {
      analogWrite(PUMP2, 0);
      Serial.println("Pump2 will turn off");
      delay(100);
    }
  }
  else if (x == PLANT3)
  {
    if (rx.getData(8) == 1)
    {
      Serial.println("Pump3 will turn on");
      analogWrite(PUMP3, 1023);
      delay(100);
    }
    else
    {
      Serial.println("Pump3 will turn off");
      analogWrite(PUMP3, 0);
      delay(100);
    }
  }
}

boolean isOverwrite(ZBRxResponse) {
  //  Serial.print("Data length = ");
  //  Serial.println(rx.getDataLength());
  if (rx.getDataLength() == OVERWRITE)
    return true;
  else
    return false;
}


void doAfterPump1() {
  Serial.println("PriorityPump1 Will now go down");
  priorityPump1 = false;
  t.stop(pump1Event);
  Serial.println("Pump1 Turned OFF");
  digitalWrite(13, LOW);
  analogWrite(PUMP1, LOW);
  delay(300);
}

void doAfterPump2() {
  Serial.println("PriorityPump2 Will now go down");
  priorityPump2 = false;
  t.stop(pump2Event);
  Serial.println("Pump2 Turned OFF");
  digitalWrite(13, LOW);
  analogWrite(PUMP2, LOW);
  delay(300);
}

void doAfterPump3() {
  Serial.println("PriorityPump3 Will now go down");
  priorityPump3 = false;
  t.stop(pump3Event);
  Serial.println("Pump3 Turned OFF");
  digitalWrite(13, LOW);
  analogWrite(PUMP3, LOW);
  delay(300);
}

// continuously reads packets, looking for ZB Receive or Modem Status
void loop()
{
  t.update();
  String x = "";
  xbee.readPacket();

  if (xbee.getResponse().isAvailable())
  {
    // got something
    Serial.println("Packet Received");
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      // got a zb rx packet

      // now fill our zb rx class
      xbee.getResponse().getZBRxResponse(rx);

      if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)
      {
        Serial.println("Acknowledgement");
        Serial.print("isOverwrite = ");
        Serial.println(isOverwrite(rx));
        x = printFrame(rx);
        if (isOverwrite(rx)) {
          if (x == PLANT1) {
            Serial.print("Plant1 Priority :");
            Serial.println(rx.getData(9));
            priorityPump1 = rx.getData(9);
            if (rx.getData(8) == HIGH) {
              Serial.println("Pump1Data ON");
              delay(100);
              digitalWrite(PUMP1, HIGH);
              delay(600);
              digitalWrite(13, HIGH);
              pump1Event = t.after(long(5000), doAfterPump1, 0);
            }
            else {
              t.stop(pump1Event);
              Serial.println("Pump1Data OFF");
              digitalWrite(PUMP1, LOW);
              delay(300);
              digitalWrite(13, LOW);
            }

          }
          else if (x == PLANT2) {
            Serial.print("Plant2 Priority :");
            Serial.println(rx.getData(9));
            priorityPump2 = rx.getData(9);
            if (rx.getData(8) == HIGH) {
              Serial.println("Pump2Data ON");
             delay(100);
              digitalWrite(PUMP2, HIGH);
              delay(600);
              digitalWrite(13, HIGH);
              pump2Event = t.after(long(5000), doAfterPump2, 0);
            }
            else {
              t.stop(pump2Event);
              Serial.println("Pump2Data OFF");
              digitalWrite(PUMP2, LOW);
               delay(300);
              digitalWrite(13, LOW);
            }
          }
          else if (x == PLANT3) {
            Serial.print("Plant3 Priority :");
            Serial.println(rx.getData(9));
            priorityPump3 = rx.getData(9);
            if (rx.getData(8) == HIGH) {
              Serial.println("Pump3Data ON");
              delay(100);
              digitalWrite(PUMP3, HIGH);
              delay(600);
              digitalWrite(13, HIGH);
              pump3Event = t.after(long(5000), doAfterPump3, 0);
            }
            else {
              t.stop(pump3Event);
              Serial.println("Pump3Data OFF");
              digitalWrite(PUMP3, LOW);
               delay(300);
              digitalWrite(13, LOW);
            }
          }
        }
//          else {
//            Serial.println("Priority off message received");
//            t.stop(LightStatusEvent);
//          }

        else if (rx.getDataLength() == 9) {
          if (priorityPump1 == false){
            Serial.println("Pump1 Normal message Received");
            performPumpingAction(x);
          }
        if (priorityPump2 == false){
            Serial.println("Pump2 Normal message Received");
            performPumpingAction(x);
        }
        if (priorityPump3 == false){
            performPumpingAction(x);
            Serial.println("Pump3 Normal message Received");
        }
      }
    }
    else
    {
      // we got it (obviously) but sender didn't get an ACK
      Serial.println("NO acknowledgement");

    }

    // set dataLed PWM to value of the first byte in the data

  }
  else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE)
  {
    xbee.getResponse().getModemStatusResponse(msr);
    // the local XBee sends this response on certain events, like association/dissociation

    if (msr.getStatus() == ASSOCIATED)
    {
      // yay this is great.  flash led
      Serial.println("Associated");
      //      flashLed(statusLed, 10, 10);
    }
    else if (msr.getStatus() == DISASSOCIATED)
    {
      // this is awful.. flash led to show our discontent
      Serial.println("Disassociated");
    }
    else
    {
      // another status
      Serial.println("Something out of scope");
    }
  }
  else
  {
    // not something we were expecting
    Serial.println("Error");
  }
}
else if (xbee.getResponse().isError())
{
  //Serial.print("Error reading packet.  Error code: ");
  //Serial.println(xbee.getResponse().getErrorCode());
}
}
