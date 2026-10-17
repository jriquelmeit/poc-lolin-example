#include <Arduino.h>

/**
 * Blink example for Lolin NodeMCU V3 (ESP8266)
 *
 * The on-board LED is connected to GPIO2 (D4 / LED_BUILTIN).
 * Note: Most ESP8266 boards have an active-low LED, meaning:
 *   - LOW  = LED ON
 *   - HIGH = LED OFF
 */

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    delay(100);
    Serial.println("\n--- Lolin NodeMCU V3 Blink Demo ---");
}

void loop() {
    // Encender LED integrado (lógica activa en bajo)
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED: ENCENDIDO");
    delay(500);

    // Apagar LED integrado
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED: APAGADO");
    delay(500);
}
