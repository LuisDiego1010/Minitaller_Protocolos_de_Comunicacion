#include <Wire.h>

// ── Configuración ──────────────────────────────────────
#define SLAVE_ADDRESS 0x08   // Dirección I2C de este slave
#define TMP36_PIN     A0     // Pin analógico del TMP36

// ── Variables globales ─────────────────────────────────
// volatile: la lee el callback I2C (que corre dentro de una interrupción)
// y la escribe el loop(). Sin volatile, el compilador podría asumir
// que no cambia y usar una copia vieja guardada en un registro.
volatile float temperatura = 0.0;
unsigned long ultimaLectura = 0;
const unsigned long INTERVALO = 1000; // 1 segundo

// ── Setup ──────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  Wire.begin(SLAVE_ADDRESS);         // Inicia I2C como Slave
  Wire.onRequest(enviarTemperatura); // Callback cuando Master pide dato

  Serial.println("Slave 1 listo");
}

// ── Loop ───────────────────────────────────────────────
void loop() {
  unsigned long ahora = millis();

  if (ahora - ultimaLectura >= INTERVALO) {
    ultimaLectura = ahora;

    // Leemos el valor analógico (0-1023) y lo convertimos a voltaje
    int lecturaCruda = analogRead(TMP36_PIN);
    float voltaje = lecturaCruda * (5.0 / 1023.0); // Convertir a voltios
    float lectura = (voltaje * 1000 - 500) / 10.0; // Convertir a °C

    // Escritura atómica: un float son 4 bytes y el AVR (8 bits) los copia
    // en varios pasos. Si el Master pidiera el dato justo a la mitad,
    // enviaríamos un valor corrupto. Por eso bloqueamos las interrupciones
    // durante la copia (dura microsegundos).
    noInterrupts();
    temperatura = lectura;
    interrupts();

    Serial.print("Temperatura: ");
    Serial.print(lectura);
    Serial.println(" °C");
  }
}

// ── Callback I2C ───────────────────────────────────────
void enviarTemperatura() {
  // Dentro del callback las interrupciones ya están deshabilitadas,
  // así que esta copia es segura.
  float t = temperatura;

  // Convertimos el float a 4 bytes y los enviamos
  byte datos[4];
  memcpy(datos, &t, 4);
  Wire.write(datos, 4);
}
