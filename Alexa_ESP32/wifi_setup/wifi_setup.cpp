#include <Arduino.h>
#include <WiFi.h>
#include "inc/credentials.h"
#include "wifi_setup/wifi_setup.h"

void wifiSetup() {
    WiFi.mode(WIFI_STA);
    Serial.printf("[WIFI] Conectando a %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(400);
    }
    Serial.println();
    Serial.printf("[WIFI] Modo STATION, SSID: %s, Dirección IP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
