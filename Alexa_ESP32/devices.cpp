#include "devices.h"

// Arreglo de dispositivos de tipo "DEVICE" (pin, id)
Device OutputDevices[] = {
  {2, "Blue lamp"},    // LED azul on board
};

// Definición del tamaño del arreglo
const int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);