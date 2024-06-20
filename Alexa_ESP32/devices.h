#ifndef DEVICES_H
#define DEVICES_H

// Enumeración para tipos de dispositivos
enum DeviceType {
    ON_OFF,     // Dispositivo ON/OFF
    DIMMABLE,   // Dispositivo con control de intensidad
};

// Estructura para representar un dispositivo
struct Device {
    int pin;        // Pin al que está conectado el dispositivo
    const char* id; // Comando de voz para el dispositivo en Alexa Home
};


// Declaración externa del arreglo de dispositivos de salida ON/OFF
extern Device OutputDevices[];
extern const int numOutputDevices; // Tamaño del arreglo de dispositivos

#endif