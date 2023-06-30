#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <LoRa.h>

byte destinationId = 0xCF;
float averageAltitude = 0.0;

Adafruit_BMP3XX bmp388;

void setup()
{
  while (!LoRa.begin(868E6))
    delay(1000);
  while (!bmp388.begin_I2C())
    delay(1000);

  bmp388.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp388.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp388.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp388.setOutputDataRate(BMP3_ODR_50_HZ);

  while (!bmp388.performReading())
  {
  }

  calibrateAltitude();
}

void loop()
{
  while (!bmp388.performReading())
  {
  }

  LoRa.beginPacket();
  LoRa.write(destinationId);

  LoRa.print(bmp388.temperature);
  LoRa.print(";");
  LoRa.print(bmp388.pressure);
  LoRa.print(";");
  LoRa.print(bmp388.readAltitude(1020.0)); // 1020 hPa ist der Luftdruck auf Meereshoehe

  LoRa.endPacket();

  delay(500);
}

void calibrateAltitude()
{
  for (int i = 0; i < 10; i++)
  {
    averageAltitude += bmp388.readAltitude(1020.0); // 1020 hPa ist der Luftdruck auf Meereshoehe
  }
  averageAltitude = averageAltitude / 10;
}