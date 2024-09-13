#include "devices.h"

// Arreglo de dispositivos de tipo "DEVICE" (pin, id)
Device OutputDevices[] = {
  {2, "LED Azul"},    // LED azul on board
  {4, "Luz TV"}
};

// Definición del tamaño del arreglo
const int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]);