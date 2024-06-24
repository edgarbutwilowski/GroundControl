#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <LoRa.h>

byte destinationId = 0xCF;
double averagePressure = 0.0;

Adafruit_BMP3XX bmp388;

void setup() {
  while (!LoRa.begin(868E6)) delay(1000);
  while (!bmp388.begin_I2C()) delay(1000);

  bmp388.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
  bmp388.setPressureOversampling(BMP3_NO_OVERSAMPLING);
  bmp388.setIIRFilterCoeff(BMP3_IIR_FILTER_DISABLE);
  bmp388.setOutputDataRate(BMP3_ODR_25_HZ);

  while (!bmp388.performReading()) delay(1000);

  calibratePressure();
}

void loop() {
  while (!bmp388.performReading()) delay(1000);

  LoRa.beginPacket();
  LoRa.write(destinationId);

  double height = (averagePressure - bmp388.pressure) / 12.5;  // 1hPa pro 8 Meter

  LoRa.println(height);

  Serial.println(height);

  LoRa.endPacket();

  delay(500);
}


void calibratePressure() {
  for (int i = 0; i < 10; i++) {
    while (!bmp388.performReading()) delay(1000);
    averagePressure += bmp388.pressure;
  }
  averagePressure = averagePressure / 10.0;
}