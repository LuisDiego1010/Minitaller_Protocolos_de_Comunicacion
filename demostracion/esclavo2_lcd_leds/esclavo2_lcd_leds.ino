#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ── Configuración ──────────────────────────────────────
#define SLAVE_ADDRESS 0x09

// Pines de los LEDs
const int LEDS[] = {3, 4, 5, 6, 7};
const int NUM_LEDS = 5;

// Zumbador de la alarma
const byte PIN_BUZZER = 8;

// Umbrales de temperatura (°C)
const float UMBRALES[] = {20.0, 30.0, 40.0, 50.0};

// LCD en dirección 0x20, 16 columnas, 2 filas
LiquidCrystal_I2C lcd(0x20, 16, 2);

// ── Variables globales ─────────────────────────────────
// volatile: las escribe el callback I2C (dentro de una interrupción)
// y las lee el loop(). Así el compilador siempre las vuelve a leer de memoria.
volatile float temperatura = 0.0;
volatile bool datoNuevo = false;

// Estado de la alarma (pitido intermitente)
bool alarma = false;
bool sonando = false;
unsigned long ultimoCambio = 0;

// ── Setup ──────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  // Iniciar I2C como Slave PRIMERO
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(recibirTemperatura); // Callback cuando Master envía dato

  // Iniciar LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }

  pinMode(PIN_BUZZER, OUTPUT);

  // Iniciar LCD
  // Nota: para escribir en la LCD este Arduino toma el control del bus,
  // es decir, también actúa como maestro (bus multi-maestro). No choca con
  // el Master porque solo escribe en la LCD después de recibir un dato.
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Esperando...");

  Serial.println("Slave 2 listo");
}

// ── Loop ───────────────────────────────────────────────
void loop() {
  if (datoNuevo) {
    // Copia atómica: tomamos el valor y bajamos la bandera sin que
    // el callback pueda interrumpir a la mitad.
    noInterrupts();
    float t = temperatura;
    datoNuevo = false;
    interrupts();

    int nivel = calcularNivel(t);
    actualizarLEDs(nivel);
    actualizarLCD(t);

    // A 50 °C o más (quinto LED) se activa la alarma
    alarma = (nivel == NUM_LEDS);
    if (!alarma) noTone(PIN_BUZZER);
  }

  sonarAlarma();
}

// ── Alarma de temperatura ──────────────────────────────
// Pitido intermitente: 250 ms
// sonando y 250 ms en silencio. Usa millis() en lugar de
// delay(), así el Arduino sigue atendiendo los mensajes I2C.
void sonarAlarma() {
  if (!alarma) return;
  if (millis() - ultimoCambio >= 250) {
    ultimoCambio = millis();
    sonando = !sonando;
    if (sonando) {
      tone(PIN_BUZZER, 880);
    } else {
      noTone(PIN_BUZZER);
    }
  }
}

// ── Callback I2C ───────────────────────────────────────
void recibirTemperatura(int bytes) {
  if (bytes == 4) {
    byte datos[4];
    for (int i = 0; i < 4; i++) {
      datos[i] = Wire.read();
    }
    // Reconstruimos el float en una variable local y luego lo asignamos.
    // (memcpy no acepta directamente un destino volatile)
    float t;
    memcpy(&t, datos, 4);
    temperatura = t;
    datoNuevo = true;
  } else {
    // Mensaje inesperado: vaciamos el buffer para no dejar basura
    while (Wire.available()) Wire.read();
  }
}

// ── Cuántos LEDs encender según la temperatura ─────────
int calcularNivel(float t) {
  int ledsEncendidos = 1; // Siempre al menos uno

  for (int i = 0; i < NUM_LEDS - 1; i++) {
    if (t >= UMBRALES[i]) {
      ledsEncendidos = i + 2;
    }
  }
  return ledsEncendidos;
}

// ── Actualizar LCD ─────────────────────────────────────
void actualizarLCD(float t) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(t, 1); // 1 decimal
  lcd.print(" C");

  Serial.print("LCD actualizada: ");
  Serial.println(t);
}

// ── Actualizar LEDs ────────────────────────────────────
void actualizarLEDs(int ledsEncendidos) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LEDS[i], i < ledsEncendidos ? HIGH : LOW);
  }

  Serial.print("LEDs encendidos: ");
  Serial.println(ledsEncendidos);
}
