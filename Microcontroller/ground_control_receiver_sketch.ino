#include <LoRa.h>

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
}

void loop()
{
    Serial.println("Serial is still working");

    Serial.println("Trying to receive long range radio packet");

    int packetSize = LoRa.parsePacket();

    if (packetSize != 0)
    {
        Serial.println("Receiving long range radio packet");
        int recipientId = LoRa.read();
        Serial.print("recipientId: ");
        Serial.println(recipientId);

        String message = "";
        while (LoRa.available())
        {
            Serial.println("Getting message");
            message += (char)LoRa.read();
        }

        if (recipientId == 0xCF)
        {
            Serial.print("message: ");
            Serial.println(message);
        }
        else
        {
            Serial.println("Message not for me");
        }
    }
}
