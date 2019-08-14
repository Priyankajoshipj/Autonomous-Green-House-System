#include <DHT.h>
#define DHTPIN A4     // what pin we're connected to
#define DHTTYPE DHT22
#define LightSensor A0
#define SoilMoistureSensor A5

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino


#define START_BYTE 0x7E
#define FRAME_TYPE 0X10
#define FRAME_ID 0x01
#define NETWORK_ADDRESS1 0xff
#define NETWORK_ADDRESS2 0xfe
#define ZB_BROADCAST_RADIUS_MAX_HOPS 0x00
#define OPTION 0x00
#define ZB_TX_API_LENGTH 14


union {
  float Temp;
  uint8_t data[4];
  
  }Temperature;
  
  union {
  float Humd;
  uint8_t data[4];
  }Humidity;
  
  union {
    float Moisture;
    uint8_t data[4];
  }SoilMoisture;
  
  union {
    float Light;
    uint8_t data[4];
  
  }LightIntensity;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print('a');
  Humidity.Humd = dht.readHumidity();
  Temperature.Temp = dht.readTemperature();
  setFrame(0x12);
  SoilMoisture.Moisture = analogRead(SoilMoistureSensor);
  LightIntensity.Light = analogRead(LightSensor);
  //Serial.print("SoilMoisture= ");
  //Serial.println(soilmoisture);
  delay(10000);
}

void setFrame(uint64_t addr) {
  int len = ZB_TX_API_LENGTH+sizeof(Temperature)+sizeof(Humidity)+sizeof(SoilMoisture)+sizeof(LightIntensity);
  uint8_t checksum = 0;
  checksum = (FRAME_TYPE + FRAME_ID + NETWORK_ADDRESS1 + NETWORK_ADDRESS2 + ZB_BROADCAST_RADIUS_MAX_HOPS + OPTION) & 0xFF;
  uint8_t msbLength, lsbLength;
  msbLength = (len >> 8) & 0xFF;
  lsbLength = len & 0xFF;
  Serial.println("msb= "); Serial.println(msbLength, HEX);
  Serial.println("lsb= "); Serial.println(lsbLength, HEX);
  Serial.print("Humidity= ");  Serial.println(Humidity.Humd);
  Serial.print("Temperature= "); Serial.println(Temperature.Temp);
  Serial.print("SoilMoisture= ");Serial.println(SoilMoisture.Moisture);
  Serial.print("LightIntensity= ");Serial.println(LightIntensity.Light);
  for (int i = 0; i < 3; i++) {
    checksum += Temperature.data[i] & 0xFF;
  }
  for (int i = 0; i < 3; i++) {
    checksum += Humidity.data[i] & 0xFF;
  }
  for (int i = 0; i < 3; i++) {
    checksum += SoilMoisture.data[i] & 0xFF;
  }
  for (int i = 0; i < 3; i++) {
    checksum += LightIntensity.data[i] & 0xFF;
  }
  checksum = 0xFF - checksum;
  Serial.print("START_BYTE= ");
  Serial.println(START_BYTE, HEX);
  Serial.write(START_BYTE);
  Serial.write(msbLength);
  Serial.write(lsbLength);
  Serial.write(FRAME_TYPE);
  Serial.write(FRAME_ID);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(0x00);
  Serial.write(NETWORK_ADDRESS1);
  Serial.write(NETWORK_ADDRESS2);
  Serial.write(ZB_BROADCAST_RADIUS_MAX_HOPS);
  Serial.write(OPTION);
  //Serial.write(0x31);
  // Serial.write(0x00);
  for (int i = 0; i < 3; i++) {
    Serial.write(Temperature.data[i]);
  }
  for (int i = 0; i < 2; i++) {
    Serial.write(Humidity.data[i]);
  }
  for (int i = 0; i < 2; i++) {
    Serial.write(SoilMoisture.data[i]);
  }
  for (int i = 0; i < 2; i++) {
    Serial.write(LightIntensity.data[i]);
  }
  Serial.write(checksum);
}

