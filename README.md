# Lolin NodeMCU V3 (ESP8266) - Blink en CLion

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Core_6-orange?logo=platformio)](https://platformio.org/)
[![ESP8266](https://img.shields.io/badge/Board-NodeMCU_V3_(ESP8266)-blue?logo=espressif)](https://www.espressif.com/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?logo=arduino)](https://www.arduino.cc/)
[![IDE](https://img.shields.io/badge/IDE-CLion-000000?logo=clion)](https://www.jetbrains.com/clion/)

Proyecto base de prueba de concepto (**PoC**) para programar y flashear el módulo **Lolin NodeMCU V3** (ESP8266) utilizando **CLion** y **PlatformIO**. Incluye un ejemplo funcional para hacer parpadear el LED integrado en la placa y emitir registros de diagnóstico por el puerto serie.

---

## Características de la Placa

* **Microcontrolador**: ESP8266 (módulo ESP-12E / ESP-12F).
* **Frecuencia de reloj**: 80 MHz (hasta 160 MHz).
* **Memoria Flash**: 4 MB.
* **Chip conversor USB a Serie**: Generalmente **WCH CH340G**.
* **LED Integrado**: Conectado a **GPIO2** (`D4` en la serigrafía NodeMCU, definido como `LED_BUILTIN`).

> [!NOTE]
> En la mayoría de las placas NodeMCU/ESP8266, el LED integrado opera con **lógica invertida (activa en bajo)**:
> * `digitalWrite(LED_BUILTIN, LOW)`: **Enciende** el LED.
> * `digitalWrite(LED_BUILTIN, HIGH)`: **Apaga** el LED.

---

## Requisitos Previos

### Hardware
* Placa de desarrollo **Lolin NodeMCU V3**.
* Cable **Micro-USB** con soporte de transferencia de datos (evitar cables exclusivos de carga).

### Software
* **CLion** (JetBrains).
* **PlatformIO Core (`pio`)**:
  ```bash
  # En macOS con Homebrew:
  brew install platformio
  ```
* **Driver USB CH340**: En versiones modernas de macOS suele estar integrado de forma nativa. Si tu sistema no reconoce el dispositivo al conectarlo, instala el driver CH34x del fabricante WCH.

---

## Estructura del Proyecto

```text
poc-lolin-example/
├── CMakeLists.txt        # Configuración CMake con targets de PlatformIO para CLion
├── platformio.ini        # Definición del entorno y placa (nodemcuv2, espressif8266)
├── src/
│   └── main.cpp          # Código fuente con lógica de parpadeo y monitor serie
├── include/              # Cabeceras personalizadas del proyecto
├── lib/                  # Librerías locales específicas
├── test/                 # Pruebas unitarias
└── .idea/                # Ajustes de proyecto y workspace para CLion / PlatformIO
```

---

## Puesta en Marcha

### 1. Clonar el Repositorio
```bash
git clone https://github.com/jriquelmeit/poc-lolin-example.git
cd poc-lolin-example
```

### 2. Abrir en CLion
1. Inicia **CLion**.
2. Selecciona **File > Open...** y elige la carpeta clonada.
3. CLion detectará y cargará automáticamente la configuración mediante `CMakeLists.txt` y los metadatos de PlatformIO.

---

## Flujo de Trabajo en CLion

En la barra superior de ejecución de CLion encontrarás los siguientes targets listos para usar:

| Target de CLion | Acción |
| :--- | :--- |
| **`PLATFORMIO_BUILD`** | Compila el firmware y genera el binario `.pio/build/nodemcuv2/firmware.bin`. |
| **`PLATFORMIO_UPLOAD`** | Compila y transfiere el binario al NodeMCU conectado por USB. |
| **`PLATFORMIO_MONITOR`** | Abre la terminal serie a 115200 baudios para ver la salida del ESP8266. |
| **`PLATFORMIO_CLEAN`** | Limpia los artefactos generados durante la compilación. |

> [!TIP]
> Para habilitar la interfaz visual completa de PlatformIO en CLion (árbol de tareas, gestor de dependencias), puedes instalar el plugin **PlatformIO for CLion** desde **Settings > Plugins**.

---

## Comandos desde Terminal

También puedes compilar y cargar el firmware directamente desde la línea de comandos:

### Compilar el proyecto
```bash
pio run
```

### Subir el firmware a la placa
Conecta la placa mediante el cable Micro-USB y ejecuta:
```bash
pio run -t upload
```

> [!IMPORTANT]
> Si tienes múltiples puertos serie o necesitas especificar uno manualmente, puedes definirlo en `platformio.ini`:
> ```ini
> upload_port = /dev/cu.usbserial-XXXX
> ```

### Monitor Serie
Para observar la salida de depuración por consola:
```bash
pio device monitor
```
*(Para salir del monitor serie, presiona `Ctrl + ]`)*

---

## Diagnóstico y Solución de Problemas

### 1. El puerto serie no es detectado
* Comprueba que el cable USB transporte datos y no solo energía.
* Lista los dispositivos conectados:
  ```bash
  pio device list
  # O en macOS:
  ls /dev/cu.*
  ```
  Debería figurar un dispositivo como `/dev/cu.usbserial-*` o `/dev/cu.wchusbserial*`.

### 2. Error al flashear (`timed out waiting for packet header`)
* Mantén presionado el botón **FLASH** del módulo NodeMCU.
* Pulsa y suelta una vez el botón **RST**.
* Suelta el botón **FLASH** y vuelve a lanzar el comando de subida.

### 3. Caracteres ilegibles en el monitor serie
* Asegúrate de que la velocidad esté fijada en **115200 baudios**, que es la configurada en `Serial.begin(115200)` y en `platformio.ini` (`monitor_speed = 115200`).
