#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include <fauxmoESP.h>

#define WIFI_SSID "ClaroFibra31-2.4"
#define WIFI_PASS "bell1234"

fauxmoESP fauxmo;

// -----------------------------------------------------------------------------

#define SERIAL_BAUDRATE     115200  // Inicial Serial_begin.

// Define el pin al que está conectado el LED azul en tu placa ESP32
#define LED_BLUE          2
#define ID_BLUE           "Blue lamp"

// Función para configurar la conexión WiFi
void wifiSetup() {
    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {

    // Inicia el puerto serial y limpia los datos previos
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println("[SETUP] Iniciando...");

    // Configura el pin del LED como salida
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, HIGH); // Enciende el LED azul

    // Configura la conexión WiFi
    wifiSetup();

    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    // Crea el servidor web para fauxmoESP
    fauxmo.createServer(true);
    fauxmo.setPort(80); // Required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // You can use different ways to invoke alexa to modify the devices state:
    // "Alexa, turn yellow lamp on"
    // "Alexa, turn on yellow lamp
    // "Alexa, set yellow lamp to fifty" (50 means 50% of brightness, note, this example does not use this functionality)

    // Add virtual devices
    fauxmo.addDevice(ID_BLUE);

    // Callback para manejar los comandos de Alexa
    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        
        // Callback when a command from Alexa is received. 
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
        // Otherwise comparing the device_name is safer.

        // Controla el LED azul según el comando de Alexa
        if (strcmp(device_name, ID_BLUE)==0) {
            digitalWrite(LED_BLUE, state ? HIGH : LOW);
        } 

    });

    Serial.println("[SETUP] Configuración completada.");

    digitalWrite(LED_BLUE, HIGH); // Enciende el LED azul

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
