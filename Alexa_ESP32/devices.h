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

// Arreglo de dispositivos de salida ON/OFF
Device OutputDevices[] = {
  {2, "Blue lamp"},    // LED azul on board
  {18, "Red lamp"},     // LED rojo ?
};

#endif