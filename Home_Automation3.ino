#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Ticker.h>

#define DHTPIN 4
#define LED1 13
#define BUZ 12
#define GASPIN 36
#define PIR 17
#define LIGHT 34

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void send_sensor();

Ticker timer;

AsyncWebServer server(80);
WebSocketsServer websockets(81);


void setup(void)
{

    Serial.begin(115200);
    pinMode(LED1, OUTPUT);
    pinMode(BUZ, OUTPUT);
    pinMode(GASPIN, INPUT);
    pinMode(PIR, INPUT);
    pinMode(LIGHT, INPUT);
    dht.begin();

    WiFi.softAP("Athena", "");
    Serial.println("softap");
    Serial.println("");
    Serial.println(WiFi.softAPIP());

    if (MDNS.begin("ESP"))
    { //esp.local/
        Serial.println("MDNS responder started");
    }

    server.on("/", [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", webpage);
    });

    server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(LED1, HIGH);
        request->send_P(200, "text/html", webpage);
    });

    server.onNotFound(notFound);

    server.begin(); // it will start webserver
    websockets.begin();
    websockets.onEvent(webSocketEvent);
    timer.attach(1, send_sensor);
}

void loop(void)
{
    websockets.loop();
}
