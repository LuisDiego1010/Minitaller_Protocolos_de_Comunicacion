// ETAPA 1 - LECTOR: leer el teclado
#include <Keypad.h>

// El teclado es una matriz: 4 filas y 4 columnas
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

void setup() {
  Serial.begin(9600);
  Serial.println(F("Lector listo. Presiona teclas."));
}

void loop() {
  char t = teclado.getKey();     // Devuelve la tecla, o 0 si no hay ninguna
  if (t) {
    Serial.print(F("Tecla: "));
    Serial.println(t);
  }
}
