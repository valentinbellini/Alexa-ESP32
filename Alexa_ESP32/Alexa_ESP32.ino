/* ==================== [INCLUSIONES] ======================================== */

#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif

#include <fauxmoESP.h>
#include "credentials.h" // Incluye el archivo de credenciales

fauxmoESP fauxmo;

/* ==================== [MACROS & TYPEDEF] ======================================== */

#define SERIAL_BAUDRATE     115200  // Serial_begin monitor

// Estructura para representar un dispositivo
struct Device {
    int pin;        // Pin al que está conectado el dispositivo
    const char* id; // Comando de voz para el dispositivo en Alexa Home
};

// Arreglo de dispositivos de salida
Device OutputDevices[] = {
  {2, "Blue lamp"},    // LED azul on board
  {4, "Red lamp"},     // LED rojo ?
};

/* ==================== [FUNCTIONS] ======================================== */

// Función para configurar la conexión WiFi
void wifiSetup() {

    WiFi.mode(WIFI_STA); // Set WIFI module to STA mode
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID); // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(400);
    }
    Serial.println();
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

// Función para configurar los dispositivos que se definan como OUTPUT
void setupOutputDevices() {
    for (const auto& device : OutputDevices) {
        pinMode(device.pin, OUTPUT);
        digitalWrite(device.pin, HIGH); // Apaga todos los dispositivos al inicio
        fauxmo.addDevice(device.id);    // Agrega el dispositivo a fauxmo
    }
}

// Setup para de la biblioteca Fauxmo
void fauxmoSetup(){
    /* By default, fauxmoESP creates it's own webserver on the defined port. The TCP port must be 80 for gen3 devices (default is 1901). This has to be done before the call to enable() */
    fauxmo.createServer(true);
    fauxmo.setPort(80); // Required for gen3 devices
    /* You have to call enable(true) once you have a WiFi connection. You can enable or disable the library at any moment. Disabling it will prevent the devices from being discovered and switched */
    fauxmo.enable(true);

    // Configura los dispositivos
    setupOutputDevices();

    // Callback para manejar los comandos de Alexa
    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        
        // Callback when a command from Alexa is received. 
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        const int numOutputDevices = sizeof(OutputDevices) / sizeof(OutputDevices[0]); // Calcula el número de dispositivos
        // Controla los dispositivos según el comando de Alexa
        for (int i = 0; i < numOutputDevices; i++) {
            if (strcmp(device_name, OutputDevices[i].id) == 0) {
                digitalWrite(OutputDevices[i].pin, state ? HIGH : LOW);
                break; // Sale del bucle una vez que se encuentra el dispositivo
            }
        }

    });

    Serial.println("[SETUP] Configuración completada.");
}

void setup() {

    // Inicia el puerto serial y limpia los datos previos
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println("[SETUP] Iniciando...");

    // Configura la conexión WiFi
    wifiSetup();

    // Configura la conexión de dispositivos con Alexa
    fauxmoSetup();
}

void loop() {

    // fauxmoESP uses an async TCP server but a sync UDP server
    // Therefore, we have to manually poll for UDP packets
    fauxmo.handle();

    // Imprime el estado de la conexión WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[MAIN] No se pudo conectar a WiFi.");
    }

    // This is a sample code to output free heap every 5 seconds
    // This is a cheap way to detect memory leaks
    static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }

    // If your device state is changed by any other means (MQTT, physical button,...)
    // you can instruct the library to report the new state to Alexa on next request:
    // fauxmo.setState(ID_YELLOW, true, 255);

}
