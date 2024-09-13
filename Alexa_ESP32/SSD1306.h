#ifndef SSD1306_H
#define SSD1306_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definiciones para el display OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

extern Adafruit_SSD1306 display;

// Funciones para manejar el OLED
void ssd1306_init();
void ssd1306_updateDisplayWiFiStatus(bool isConnected);
void ssd1306_updateDisplayLEDStatus(bool ledState);
void ssd1306_updateDisplayHeap();

#endif // SSD1306_H
