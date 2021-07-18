void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{

    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    }
    break;
    case WStype_TEXT:
        Serial.printf("[%u] get Text: %s\n", num, payload);
        String message = String((char *)(payload));
        Serial.println(message);

        DynamicJsonDocument doc(200);
        // deserialize the data
        DeserializationError error = deserializeJson(doc, message);
        
        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        int LED1_status = doc["LED1"];
        int BUZ_status = doc["BUZ"];
        digitalWrite(LED1, LED1_status);
        digitalWrite(BUZ, BUZ_status);
    }
}
