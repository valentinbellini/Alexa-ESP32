
/* ======================================== [ INCLUSIONES ] ======================================== */

#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif

#include <fauxmoESP.h>
#include "devices.h"
#include "WifiSetup.h"
#include "FauxmoSetup.h"
#include "SSD1306.h"

fauxmoESP fauxmo;

/* ======================================== [ MACROS & TYPEDEF ] ======================================== */

#define SERIAL_BAUDRATE     115200  // Serial_begin monitor

/* ======================================== [ VARIABLES ] ======================================== */
  
int freeHeap = 0;
String ssid = "Buscando...";

/* ======================================== [ SET UP ] ======================================== */

void setup() {
    // Inicia el puerto serial y limpia los datos previos
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println("[MAIN SETUP] Iniciando...");

    // Inicializa el Display OLED
    ssd1306_init();

    // Configura la conexión WiFi
    wifiSetup();

    // Configura la conexión de dispositivos con Alexa
    fauxmoSetup();

}

/* ======================================== [ LOOP ] ======================================== */

void loop() {

    // fauxmoESP uses an async TCP server but a sync UDP server
    // Therefore, we have to manually poll for UDP packets
    fauxmo.handle();
    
   
    bool isConnected = WiFi.status() == WL_CONNECTED;

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[MAIN] No se pudo conectar a WiFi.");
    } else {
    }
    
    // Obtener el estado del LED (por ejemplo, en el pin 2)
    bool ledState = digitalRead(4);


    // This is a sample code to output free heap every 5 seconds
    // This is a cheap way to detect memory leaks
    static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
        freeHeap = ESP.getFreeHeap(); 
        ssid = WiFi.SSID();
    }

    // Actualizar la pantalla con la información
    ssd1306_displayInfo(ssid, isConnected, ledState, freeHeap);

    
    // Ejemplo de código para obtener el estado del pin 2 (LED azul)
    // int ledState = digitalRead(2); // Leer el estado del pin 2
    // digitalWrite(12, ledState ? HIGH : LOW);

    // If your device state is changed by any other means (MQTT, physical button,...)
    // you can instruct the library to report the new state to Alexa on next request:
    // fauxmo.setState(ID_YELLOW, true, 255);

    delay(100);

}
