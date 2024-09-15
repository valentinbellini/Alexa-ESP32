#ifndef SSD1306_H
#define SSD1306_H

#include <Adafruit_SSD1306.h>  // Librería del display

// Definir dimensiones de la pantalla
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Pin de reset (puedes usar -1 si no lo usas)

// Crear la instancia del display
extern Adafruit_SSD1306 display;

// Función para inicializar el display
void ssd1306_init();

// Función para actualizar el estado del WiFi en el display
void ssd1306_updateDisplayWiFiStatus(bool isConnected);

// Función para actualizar el estado del LED en el display
void ssd1306_updateDisplayLEDStatus(bool ledState);

// Función para mostrar la memoria heap libre
void ssd1306_updateDisplayHeap();

// Función para mostrar toda la información (WiFi, LED, Heap) en el display
void ssd1306_displayInfo(String ssid, bool isConnected, bool ledState, int freeHeap);

#endif  // SSD1306_H
