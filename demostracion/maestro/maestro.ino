#include <Wire.h>

// ── Configuración ──────────────────────────────────────
#define SLAVE1_ADDRESS 0x08  // Sensor TMP36
#define SLAVE2_ADDRESS 0x09  // LCD + LEDs

const unsigned long INTERVALO = 1000; // 1 segundo

// ── Variables globales ─────────────────────────────────
unsigned long ultimaLectura = 0;
float temperatura = 0.0;

// ── Setup ──────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  Wire.begin(); // Inicia I2C como Master (sin dirección)

  Serial.println("Master listo");
}

// ── Loop ───────────────────────────────────────────────
void loop() {
  unsigned long ahora = millis();

  if (ahora - ultimaLectura >= INTERVALO) {
    ultimaLectura = ahora;

    if (leerTemperatura()) {
      enviarASlave2();
    }
  }
}

// ── Leer temperatura del Slave 1 ───────────────────────
bool leerTemperatura() {
  Wire.requestFrom(SLAVE1_ADDRESS, 4); // Pedimos 4 bytes

  if (Wire.available() == 4) {
    byte datos[4];
    for (int i = 0; i < 4; i++) {
      datos[i] = Wire.read();
    }
    memcpy(&temperatura, datos, 4); // Reconstruimos el float

    Serial.print("[Master] Temperatura recibida: ");
    Serial.print(temperatura);
    Serial.println(" °C");
    return true;
  }

  Serial.println("[Master] Error: Slave 1 no respondió");
  return false;
}

// ── Enviar temperatura al Slave 2 ──────────────────────
void enviarASlave2() {
  byte datos[4];
  memcpy(datos, &temperatura, 4); // Convertimos float a bytes

  Wire.beginTransmission(SLAVE2_ADDRESS);
  Wire.write(datos, 4);
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("[Master] Dato enviado al Slave 2 OK");
  } else {
    Serial.print("[Master] Error enviando a Slave 2, código: ");
    Serial.println(error);
  }
}