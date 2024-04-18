
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

fauxmoESP fauxmo;

/* ======================================== [ MACROS & TYPEDEF ] ======================================== */

#define SERIAL_BAUDRATE     115200  // Serial_begin monitor

/* ======================================== [ FUNCTIONS ] ======================================== */

// Setup para de la biblioteca Fauxmo
void fauxmoSetup(){
    /* By default, fauxmoESP creates it's own webserver on the defined port. The TCP port must be 80 for gen3 devices (default is 1901). This has to be done before the call to enable() */
    fauxmo.createServer(true);
    fauxmo.setPort(80); // Required for gen3 devices
    /* You have to call enable(true) once you have a WiFi connection. You can enable or disable the library at any moment. Disabling it will prevent the devices from being discovered and switched */
    fauxmo.enable(true);

    // Configura los dispositivos
    setupOutputDevices();

    // Callback para manejar los comandos de Alexa
    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        // Callback when a command from Alexa is received. 
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        
        // Controla los dispositivos según el comando de Alexa
        static int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);
        for (int i = 0; i < numOutputDevices; i++) { 
            if (strcmp(device_name, OutputDevices[i].id) == 0) {  // Si la comparación coincide --> se encontró el dispositivo.
              digitalWrite(OutputDevices[i].pin, state ? HIGH : LOW);
              break; // Sale del bucle una vez que se encuentra el dispositivo
            }
        }
    });
    Serial.println("[FAUXMO SETUP] Configuración completada.");
}

// Función para configurar los dispositivos que se definan como OUTPUT y agregar dispositivo a fauxmo
void setupOutputDevices() {
    for (const auto& device : OutputDevices) {
        pinMode(device.pin, OUTPUT);
        digitalWrite(device.pin, HIGH); // Apaga todos los dispositivos al inicio
        fauxmo.addDevice(device.id);    // Agrega el dispositivo a fauxmo
    }
}

/* ======================================== [ SET UP ] ======================================== */

void setup() {

    // Inicia el puerto serial y limpia los datos previos
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println("[MAIN SETUP] Iniciando...");

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

    // Imprime el estado de la conexión WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[MAIN] No se pudo conectar a WiFi.");
    }

    // This is a sample code to output free heap every 5 seconds
    // This is a cheap way to detect memory leaks
    static unsigned long last = millis();
    if (millis() - last > 10000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }

    // If your device state is changed by any other means (MQTT, physical button,...)
    // you can instruct the library to report the new state to Alexa on next request:
    // fauxmo.setState(ID_YELLOW, true, 255);

}
