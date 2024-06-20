#include <Arduino.h>
#include <fauxmoESP.h>
#include "devices.h"
#include "FauxmoSetup.h"

extern fauxmoESP fauxmo; // Declarar la instancia externa de fauxmo

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
        
        Serial.printf("[FAUXMO SETUP] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        
        // Controla los dispositivos según el comando de Alexa
        // static int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);
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
    for (int i = 0; i < numOutputDevices; ++i) {
        pinMode(OutputDevices[i].pin, OUTPUT);
        digitalWrite(OutputDevices[i].pin, HIGH); // Apaga todos los dispositivos al inicio
        fauxmo.addDevice(OutputDevices[i].id);    // Agrega el dispositivo a fauxmo
    }
}
