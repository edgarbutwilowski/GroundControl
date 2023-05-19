#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <LoRa.h>

byte destinationId = 0xCF;

Adafruit_BMP3XX bmp388;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.println("Serial port ready");
  while (!LoRa.begin(868E6))
  {
    Serial.println("Long range radio NOT working");
    delay(1000);
  }
  int i = 1;
  while (!bmp388.begin_I2C())
  {
    Serial.print("BMP NOT working ");
    Serial.println(i);
    i++;
    delay(1000);
  }

  bmp388.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp388.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp388.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp388.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop()
{
  Serial.println("Serial is still working");

  Serial.println("Sending long range radio packet");

  LoRa.beginPacket();
  LoRa.write(destinationId);
  LoRa.print("test");
  LoRa.endPacket();

  if (!bmp388.performReading())
  {
    Serial.println("Could not read pressure sensor");
  }

  Serial.print("Temperatur: ");
  Serial.print(bmp388.temperature);
  Serial.println(" C");

  Serial.print("Luftdruck: ");
  Serial.print(bmp388.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Hoehe: ");
  Serial.print(bmp388.readAltitude(1020.0)); // 1020 hPa ist der Luftdruck auf Meereshoehe
  Serial.println(" m");

  delay(1000);
}


float calibrateAltitude(){
  float averageAltitude = 0.0;
  for(int i = 0; i < 10; i++){
    averageAltitude += bmp388.readAltitude(1020.0); // 1020 hPa ist der Luftdruck auf Meereshoehe
  }
  return averageAltitude / 10;
}