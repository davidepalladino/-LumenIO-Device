#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <Servo.h>

#include "configMain.h"
#include "configWiFi.h"
#include "configServer.h"

WiFiServer server(portServer);

uint8_t message[255] {0};
int last = 0;

void setup() {
  Serial.begin(115200);

  Serial.print("\nConnection to WiFi..");
  WiFi.begin(wifiSSID, wifiPassword);
  WiFi.hostname(wifiHostname);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n\tIP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("\tHostname: ");
  Serial.println(WiFi.hostname());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected...");
    while (client.connected()) {
      int read = Serial.read();

      if (read > 0 && read != last) {
        Serial.println("Changed");
        last = read;
        client.write(read);
      }

      while (client.available() != 0) {
        client.read(message, 255);
        Serial.print((char*) message);
      }
    }

    Serial.println("Client disconnected...");
    client.stop();
  }
}