# Control de Dispositivos con Alexa y Arduino

Este proyecto te permite controlar dispositivos utilizando comandos de voz a través de Alexa, utilizando un microcontrolador Arduino (ya sea ESP32 o ESP8266) y la biblioteca FauxmoESP.

## Descripción

El proyecto utiliza la biblioteca FauxmoESP para emular dispositivos inteligentes compatibles con Alexa en un microcontrolador Arduino. Esto permite controlar dispositivos físicos como luces, relés, ventiladores, etc., utilizando comandos de voz a través de cualquier dispositivo Amazon Echo.

La biblioteca FauxmoESP implementa un servidor UPnP que simula un dispositivo compatible con Wemo, el cual es reconocido automáticamente por Alexa. Una vez que Alexa detecta los dispositivos, puedes controlarlos utilizando comandos de voz como "Alexa, enciende la luz". Para esto será necesario vincular los dispositivos con Alexa mediante la aplicación.

## Detalles Técnicos

- **Microcontrolador**: Se puede utilizar tanto el ESP32 como el ESP8266.
- **Biblioteca FauxmoESP**: Emula dispositivos compatibles con Wemo para interactuar con Alexa.
- **Conexión WiFi**: La placa se conecta a la red WiFi local para comunicarse con los dispositivos Amazon Echo.
- **Credenciales de WiFi**: Se almacenan de forma segura en el archivo `credentials.h`.
- **Configuración de Dispositivos**: Los dispositivos físicos se definen en la estructura `Device` dentro del código Arduino.
- **Comandos de Voz**: Se pueden utilizar comandos de voz predefinidos para controlar los dispositivos emulados por Alexa.

## Instalación

1. Descarga e instala el entorno de desarrollo Arduino en tu computadora si aún no lo has hecho.
2. Clona o descarga este repositorio en tu computadora.
3. Abre el archivo `Alexa_ESP32.ino` o `Alexa_ESP8266.ino` en Arduino IDE.
4. Instala las bibliotecas necesarias si aún no están instaladas:
   - FauxmoESP: [Instrucciones de instalación](https://github.com/vintlabs/fauxmoESP#installation).
   - WiFi (dependiendo de tu placa): Si estás utilizando ESP8266, necesitarás instalar `ESP8266WiFi`. Si estás utilizando ESP32, necesitarás instalar `WiFi`.
5. Configura tus credenciales de WiFi en el archivo `credentials.h`.
6. Conecta tu placa Arduino a tu computadora y selecciona el puerto correcto y el tipo de placa en Arduino IDE.
7. Sube el código a tu placa Arduino.

## Configuración

1. Abre el archivo `credentials.h` y agrega tu SSID y contraseña de WiFi.
2. Abre el archivo `Alexa_ESP32.ino` o `Alexa_ESP8266.ino` y modifica la estructura `Device` en la parte superior del archivo para representar tus dispositivos. Agrega tantos dispositivos como desees controlar. Debes indicar pin y comando de voz.

## Uso

1. Enciende tu dispositivo Arduino.
2. Abre la aplicación Alexa en tu dispositivo móvil.
3. Ve a la sección de dispositivos y escanea en busca de nuevos dispositivos.
4. Alexa debería detectar los dispositivos que has configurado y podrás controlarlos mediante comandos de voz.

## Contribuciones

Las contribuciones son bienvenidas. Si tienes sugerencias de mejora, por favor abre un problema o envía una solicitud de extracción.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.

