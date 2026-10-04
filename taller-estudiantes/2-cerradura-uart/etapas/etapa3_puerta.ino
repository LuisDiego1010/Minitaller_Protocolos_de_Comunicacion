// ETAPA 3 - PUERTA: recibir por UART y mostrar lo que llega
#include <SoftwareSerial.h>

const long BAUD_UART = 1200;     // Igual que en el Lector

SoftwareSerial uart(10, 11);     // RX = ~10, TX = ~11

void setup() {
  Serial.begin(9600);
  uart.begin(BAUD_UART);
  Serial.println(F("Puerta lista. Esperando..."));
}

void loop() {
  if (uart.available()) {        // Llego al menos un byte?
    char c = uart.read();        // Lo tomamos
    Serial.write(c);             // Y lo mostramos tal cual
  }
}
