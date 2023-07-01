#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <LoRa.h>

byte destinationId = 0xCF;
double averagePressure = 0.0;

Adafruit_BMP3XX bmp388;

void setup()
{
  while (!LoRa.begin(868E6))
    delay(1000);
  while (!bmp388.begin_I2C())
    delay(1000);

  bmp388.setOutputDataRate(BMP3_ODR_25_HZ);
  bmp388.setPressureOversampling(BMP3_NO_OVERSAMPLING);
  bmp388.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);

  while (!bmp388.performReading())
  {
  }

  calibratePressure();
}

void loop()
{
  while (!bmp388.performReading())
  {
  }

  LoRa.beginPacket();
  LoRa.write(destinationId);

  double altitude = (averagePressure - bmp388.pressure) / 8.0;
  LoRa.print(altitude);

  LoRa.endPacket();

  delay(100);
}

void calibratePressure()
{
  for (int i = 0; i < 10; i++)
  {
    while (!bmp388.performReading())
    {
    }
    averagePressure += bmp388.pressure;
  }
  averagePressure = averagePressure / 10;
}