#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

Adafruit_BMP3XX bmp388;

void setup() {
  Serial.begin(9600);
  while(!Serial){}
  Serial.println("Serial port ready");
  while(!bmp388.begin_I2C()){
    Serial.println("Serial NOT working");
  }

}

void loop() {
  Serial.println("Serial is working");
  bmp388.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp388.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp388.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp388.setOutputDataRate(BMP3_ODR_50_HZ);

  if(!bmp388.performReading()){
    Serial.println("Serial NOT working");
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(bmp388.temperature);
  Serial.println(" C");

  Serial.print("Luftdruck: ");
  Serial.print(bmp388.pressure / 100.0);
  Serial.println(" hPa");


}
