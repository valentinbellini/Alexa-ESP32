
// Definición e inicialización del arreglo de dispositivos de salida ON/OFF
#include "HAL_Device/HAL_devices.h"

// Arreglo de dispositivos de salida
Device OutputDevices[] = {
    {2, "Blue lamp", ON_OFF},  // LED azul on board
    {18, "Red lamp", ON_OFF}   // LED rojo (Rly)
};
