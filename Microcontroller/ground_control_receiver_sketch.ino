#include <LoRa.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    while (!LoRa.begin(868E6))
    {
        Serial.println("ERR-1");
        delay(1000);
    }
}

void loop()
{
    int packetSize = LoRa.parsePacket();

    if (packetSize != 0)
    {
        int recipientId = LoRa.read();
        if (recipientId == 0xCF)
        {
            String message = "";
            while (LoRa.available())
            {
                message += (char)LoRa.read();
            }
            Serial.println(message);
        }
        else
        {
            Serial.println("ERR-2");
        }
    }
}