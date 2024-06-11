#include <Arduino.h>
#include <fauxmoESP.h>
#include "HAL_Device/HAL_devices.h"
#include "fauxmo_ESP/inc/fauxmo_control.h"

// Función para configurar los dispositivos que se definan como OUTPUT y agregar dispositivo a fauxmo
void setupOutputDevices() {
    for (const auto& device : OutputDevices) {
        pinMode(device.pin, OUTPUT);
        digitalWrite(device.pin, HIGH); // Apaga todos los dispositivos al inicio
        fauxmo.addDevice(device.id);    // Agrega el dispositivo a fauxmo
    }
}

void handleAlexaCommand(const char* device_name, bool state) {
    static int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);
    for (int i = 0; i < numOutputDevices; i++) { 
        if (strcmp(device_name, OutputDevices[i].id) == 0) {  // Si la comparación coincide --> se encontró el dispositivo.
            digitalWrite(OutputDevices[i].pin, state ? HIGH : LOW);
            OutputDevices[i].state = state; // Actualizamos el estado del dispositivo
            break; // Sale del bucle una vez que se encuentra el dispositivo
        }
    }
}
