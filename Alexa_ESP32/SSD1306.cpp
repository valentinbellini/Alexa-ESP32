#include "SSD1306.h"
#include <Arduino.h>

// Crear la instancia del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Función para inicializar el display
void ssd1306_init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Dirección I2C 0x3C
        Serial.println(F("SSD1306 allocation failed"));
        for (;;) ; // En caso de error, detener el sistema
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Iniciando ESP32"));
    display.display();
}

// Actualizar el estado del WiFi en el display
void ssd1306_updateDisplayWiFiStatus(bool isConnected) {
    display.clearDisplay();

    // Texto para mostrar
    String text = isConnected ? "Conectado a WiFi" : "No conectado a WiFi";

    // Calcular coordenadas centradas
    int16_t x = (SCREEN_WIDTH - text.length() * 6) / 2;  // Centrar horizontalmente
    int16_t y = (SCREEN_HEIGHT / 8);  // Aproximadamente en la parte superior (25% de la altura)

    display.setCursor(x, y);
    display.println(text);
    display.display();
}

// Actualizar el estado del LED en el display
void ssd1306_updateDisplayLEDStatus(bool ledState) {
    // Texto para mostrar
    String text = ledState ? "LED State: ON" : "LED State: OFF";

    // Calcular coordenadas centradas
    int16_t x = (SCREEN_WIDTH - text.length() * 6) / 2;  // Centrar horizontalmente
    int16_t y = (SCREEN_HEIGHT / 2) - 4;  // Centrar verticalmente

    display.setCursor(x, y);
    display.println(text);
    display.display();
}

// Actualizar la memoria libre en el display
void ssd1306_updateDisplayHeap() {
    // Texto para mostrar
    String text = "Free Heap: " + String(ESP.getFreeHeap()) + " bytes";

    // Calcular coordenadas centradas
    int16_t x = (SCREEN_WIDTH - text.length() * 6) / 2;  // Centrar horizontalmente
    int16_t y = (SCREEN_HEIGHT * 3 / 4) - 4;  // En la parte inferior (75% de la altura)

    display.setCursor(x, y);
    display.println(text);
    display.display();
}
