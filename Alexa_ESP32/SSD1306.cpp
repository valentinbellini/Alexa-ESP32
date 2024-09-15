#include "SSD1306.h"
#include <Arduino.h>

#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif

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
    display.setCursor(50, 25);
    display.println(F("Iniciando ESP32"));
    display.display();
}

// Mostrar la red WiFi, estado del LED y Heap
void ssd1306_displayInfo(String ssid, bool isConnected, bool ledState, int freeHeap) {
  display.clearDisplay();

  // Mostrar la red WiFi
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("WiFi: ");
  display.println(isConnected ? ssid : "Desconectado");

  // Mostrar una barra de señal (basado en RSSI)
  int16_t signalStrength = WiFi.RSSI();  // Obtener la señal de WiFi
  int16_t signalBarWidth = map(signalStrength, -100, -30, 0, 50);  // Mapear la intensidad a una barra
  display.drawRect(0, 10, 50, 8, SSD1306_WHITE);  // Dibujar el contorno
  display.fillRect(0, 10, signalBarWidth, 8, SSD1306_WHITE);  // Rellenar la barra

  // Mostrar el estado del LED
  display.setCursor(0, 25);
  display.print("LED: ");
  display.println(ledState ? "ON" : "OFF");

  // Dibujar un círculo para el estado del LED (rojo si está apagado, verde si está encendido)
  if (ledState) {
      display.fillCircle(70, 28, 5, SSD1306_WHITE);  // LED encendido
  } else {
      display.drawCircle(70, 28, 5, SSD1306_WHITE);  // LED apagado
  }

  // Mostrar el heap libre
  display.setCursor(0, 40);
  display.print("Heap: ");
  display.println(String((ESP.getHeapSize()-freeHeap) / 1000) + "/" + String(ESP.getHeapSize() / 1000) + " Kb");

  // Dibujar una barra para el heap libre
  int16_t heapBarWidth = map(ESP.getHeapSize()-freeHeap, 0, ESP.getHeapSize(), 0, 50);  // Mapear el heap al tamaño de la barra
  display.drawRect(0, 50, 50, 8, SSD1306_WHITE);  // Dibujar el contorno de la barra
  display.fillRect(0, 50, heapBarWidth, 8, SSD1306_WHITE);  // Rellenar la barra con el porcentaje de heap


  // Mostrar todo
  display.display();
}
