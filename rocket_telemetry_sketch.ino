#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <LoRa.h>

Adafruit_BMP280 bmp280;

void setup() {
  Serial.begin(9600);
  while(!Serial){}
  Serial.println("Serial port ready");
  while(!LoRa.begin(868E6)){
    Serial.println("Long range radio NOT working");
    delay(1000);
  }
  while(!bmp280.begin()){
    Serial.println("BMP NOT working 1");
    delay(1000);
  }

}

void loop() {
  Serial.println("Serial is still working");

  Serial.println("Sending long range radio packet");

  LoRa.beginPacket();
  LoRa.print("test");
  LoRa.endPacket();

  Serial.print("Temperatur: ");
  Serial.print(bmp280.readTemperature());
  Serial.println(" C");

  Serial.print("Luftdruck: ");
  Serial.print(bmp280.readPressure() / 100.0);
  Serial.println(" hPa");

  Serial.print("Hoehe: ");
  Serial.print(bmp280.readAltitude(1020.0)); // 1020 hPa ist der Luftdruck auf Meereshoehe
  Serial.println(" m");

  delay(1000);

}
