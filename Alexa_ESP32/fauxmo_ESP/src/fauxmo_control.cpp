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

void handleAlexaCommand(unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    static int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);
    for (int i = 0; i < numOutputDevices; i++) { 
        if (strcmp(device_name, OutputDevices[i].id) == 0) {  // Si la comparación coincide --> se encontró el dispositivo.
            if (OutputDevices[i].type == ON_OFF) {
                digitalWrite(OutputDevices[i].pin, state ? HIGH : LOW);
                OutputDevices[i].state = state; // Actualizamos el estado del dispositivo
            } else if (OutputDevices[i].type == DIMMABLE) {
                // Ajustar la intensidad del dispositivo demirizable (por ejemplo, un LED dimmable)
                // El valor de intensidad (value) es un número entre 0 y 255, donde 0 es apagado y 255 es el brillo máximo
                analogWrite(OutputDevices[i].pin, value);
                OutputDevices[i].intensity = value; // Actualizamos la intensidad del dispositivo
                OutputDevices[i].state = (value > 0); // Si la intensidad es mayor que 0, el estado es ON, de lo contrario, OFF
            }
            break; // Sale del bucle una vez que se encuentra el dispositivo
        }
    }
}

