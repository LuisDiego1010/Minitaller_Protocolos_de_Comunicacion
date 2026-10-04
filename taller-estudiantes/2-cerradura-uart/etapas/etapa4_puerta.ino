// ETAPA 4 - PUERTA: armar el mensaje, verificar el codigo y usar los LEDs
#include <SoftwareSerial.h>

const long BAUD_UART = 1200;
const char CODIGO_CORRECTO[] = "1958";

const byte PIN_LED_VERDE = 6;    // Puerta abierta
const byte PIN_LED_ROJO  = 7;    // Puerta cerrada

SoftwareSerial uart(10, 11);

char recibido[17];               // Aqui se arma el mensaje
byte largo = 0;

void setup() {
  Serial.begin(9600);
  uart.begin(BAUD_UART);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  digitalWrite(PIN_LED_ROJO, HIGH);   // Arranca cerrada
  Serial.println(F("Puerta lista. Esperando codigo..."));
}

void loop() {
  if (!uart.available()) return;

  char c = uart.read();
  Serial.write(c);

  if (c == '\r') return;           // Se ignora
  if (c == '\n') {                 // Fin del mensaje: verificamos
    recibido[largo] = '\0';
    verificar();
    largo = 0;
  } else if (largo < 16) {         // Seguimos armando el mensaje
    recibido[largo++] = c;
  }
}

void verificar() {
  if (strcmp(recibido, CODIGO_CORRECTO) == 0) {
    digitalWrite(PIN_LED_ROJO, LOW);
    digitalWrite(PIN_LED_VERDE, HIGH);
    Serial.println(F("PUERTA ABIERTA"));
  } else {
    Serial.println(F("Codigo invalido"));
  }
}
