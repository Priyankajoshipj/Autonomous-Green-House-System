#include "Timer.h"

Timer t;

int LightStatusEvent;
boolean priority = false;

#include <XBee.h>


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
  pinMode(4, OUTPUT);
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

void performLightingAction(String x) {

  if (x == PLANT1 || x == PLANT2 || x == PLANT3)
  {
    if (rx.getData(8) == 1) {
      Serial.println("Light will turn On");
      digitalWrite(13, HIGH);
      digitalWrite(4, HIGH);
      delay(400);
    }
    else
    {
      Serial.println("Light will turn off");
      digitalWrite(13, LOW);
      digitalWrite(4, LOW);
      delay(400);
    }
    // set dataLed PWM to value of the first byte in the data
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



void doAfter() {
  Serial.println("Priority Will now go down");
  priority = false;
  t.stop(LightStatusEvent);
  Serial.println("Light Turned OFF");
  digitalWrite(13, LOW);
  digitalWrite(4, LOW);
  delay(400);
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
          priority = rx.getData(9);

          if (priority) {
            Serial.println("Priority is HIGH");
            if (rx.getData(8) == HIGH) {
              Serial.println("LightData ON");
              digitalWrite(4, HIGH);
              delay(400);
              digitalWrite(13, HIGH);
               LightStatusEvent = t.after(long(5000), doAfter, 0);
            }
            else {
              t.stop(LightStatusEvent);
              Serial.println("LightData OFF");
              digitalWrite(4, LOW);
              delay(400);
              digitalWrite(13, LOW);
              priority=false;
            }
           
          }
          else {
            Serial.println("Priority off message received");
            t.stop(LightStatusEvent);
          }
        }
        else if (rx.getDataLength() == 9) {
          Serial.print("Priority is ");
          Serial.println(priority);
          Serial.println("Plant message received");
          if (priority == false)
            performLightingAction(x);
        }
      }
      else
      {
        // we got it (obviously) but sender didn't get an ACK
        Serial.println("NO acknowledgement");

      }
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
