#ifndef HAL_DEVICES_H
#define HAL_DEVICES_H

#include <Arduino.h>


// Enumeración para tipos de dispositivos
enum DeviceType {
    ON_OFF,     // Dispositivo ON/OFF
    DIMMABLE,   // Dispositivo con control de intensidad
};

// Estructura para representar un dispositivo
struct Device {
    int pin;          // Pin al que está conectado el dispositivo
    const char* id;   // Comando de voz para el dispositivo en Alexa Home
    DeviceType type;  // Tipo de dispositivo
    bool state;       // Estado actual del dispositivo
    int intensity;    // Intensidad del dispositivo (solo para dispositivos DIMMABLE)
};

// Arreglo de dispositivos de salida
extern Device OutputDevices[];


#endif