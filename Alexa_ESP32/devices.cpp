#include "devices.h"

// Definición del arreglo de dispositivos de salida ON/OFF
Device OutputDevices[] = {
  {2, "Blue lamp"},    // LED azul on board
};

// Definición del tamaño del arreglo
const int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);