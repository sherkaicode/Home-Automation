void send_sensor()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature(); // Temp Sensor Read
    int p = digitalRead(PIR);
    float g = analogRead(GASPIN); // Gas Module Read
    float f = (t * 1.8) + 32;
    if (isnan(h) || isnan(t) || isnan(g))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    String JSON_Data = "{\"temp\":";
    JSON_Data += t;
    JSON_Data += ",\"hum\":";
    JSON_Data += h;
    JSON_Data += ",\"gas\":";
    JSON_Data += g;
    JSON_Data += ",\"pir\":";
    JSON_Data += p;
    JSON_Data += ",\"far\":";
    JSON_Data += f;
    JSON_Data += "}";
    Serial.println(JSON_Data);
    websockets.broadcastTXT(JSON_Data);
}
