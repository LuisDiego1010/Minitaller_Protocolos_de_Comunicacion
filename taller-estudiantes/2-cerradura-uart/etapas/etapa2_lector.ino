// ETAPA 2 - LECTOR: armar el codigo y enviarlo por UART
#include <Keypad.h>
#include <SoftwareSerial.h>

const long BAUD_UART = 1200;     // Debe ser igual en el Lector y en la Puerta

SoftwareSerial uart(10, 11);     // RX = ~10, TX = ~11

const byte FILAS = 4, COLS = 4;
char teclas[FILAS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinesFilas[FILAS] = {9, 8, 7, 6};   // Row 1..4
byte pinesCols[COLS]   = {5, 4, 3, 2};   // Column 1..4
Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesCols, FILAS, COLS);

char codigo[9];                  // Hasta 8 digitos + el fin de texto
byte largo = 0;

void setup() {
  Serial.begin(9600);
  uart.begin(BAUD_UART);
  Serial.println(F("Lector listo. Escribi el codigo y presiona #"));
}

void loop() {
  char t = teclado.getKey();
  if (!t) return;

  if (t == '#') {                  // Enviar: el codigo y un '\n' que marca el final
    codigo[largo] = '\0';
    uart.print(codigo);
    uart.print('\n');
    Serial.print(F(" -> enviado: "));
    Serial.println(codigo);
    largo = 0;
  } else if (t == '*') {           // Borrar
    largo = 0;
    Serial.println(F(" (borrado)"));
  } else if (largo < 8) {          // Guardar la tecla
    codigo[largo++] = t;
    Serial.print('*');
  }
}
