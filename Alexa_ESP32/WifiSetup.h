#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <ESP.h>
#include "credentials.h" // Incluye el archivo de credenciales

// Función para configurar la conexión WiFi
void wifiSetup() {
    WiFi.mode(WIFI_STA); // Set WIFI module to STA mode
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID); // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(400);
    }
    Serial.println();
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

#endif