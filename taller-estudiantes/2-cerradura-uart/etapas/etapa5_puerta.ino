// ETAPA 5 - PUERTA: version completa con zumbador y pantalla
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const long BAUD_UART = 1200;
const char CODIGO_CORRECTO[] = "1958";

// El fragmento 2 guardado como codigos ASCII (cada byte es una letra)
const byte FRAGMENTO_2[] = {0x63, 0x65, 0x72, 0x72, 0x6F, 0x6A, 0x6F};

const byte PIN_LED_VERDE = 6;    // Puerta abierta
const byte PIN_LED_ROJO  = 7;    // Puerta cerrada
const byte PIN_BUZZER    = 8;

SoftwareSerial uart(10, 11);          // RX = ~10, TX = ~11
LiquidCrystal_I2C lcd(0x20, 16, 2);   // SDA = A4, SCL = A5

char recibido[17];
byte largo = 0;
unsigned long ultimo = 0;        // Momento del ultimo byte recibido

void setup() {
  Serial.begin(9600);
  uart.begin(BAUD_UART);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  lcd.init();
  lcd.backlight();
  cerrar();
  Serial.println(F("Puerta lista"));
}

void loop() {
  if (!uart.available()) return;

  char c = uart.read();
  Serial.write(c);

  if (millis() - ultimo > 1000) largo = 0;   // Resto de un mensaje viejo: se descarta
  ultimo = millis();

  if (c == '\r') return;
  if (c == '\n') {
    recibido[largo] = '\0';
    verificar();
    largo = 0;
  } else if (largo < 16) {
    recibido[largo++] = c;
  } else {
    largo = 0;
  }
}

void verificar() {
  if (strcmp(recibido, CODIGO_CORRECTO) == 0) {
    abrir();
  } else {
    mostrar("Codigo invalido", "");
    tone(PIN_BUZZER, 200, 300);
    delay(1000);
    cerrar();
  }
}

void abrir() {
  digitalWrite(PIN_LED_ROJO, LOW);
  digitalWrite(PIN_LED_VERDE, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Acceso concedido");
  lcd.setCursor(0, 1); lcd.print("Frag 2: ");
  for (byte i = 0; i < sizeof(FRAGMENTO_2); i++) {
    lcd.print((char)FRAGMENTO_2[i]);         // Cada codigo ASCII se muestra como letra
  }
  tone(PIN_BUZZER, 784, 300);
  Serial.println(F("PUERTA ABIERTA"));
}

void cerrar() {
  digitalWrite(PIN_LED_VERDE, LOW);
  digitalWrite(PIN_LED_ROJO, HIGH);
  mostrar("Puerta cerrada", "Ingrese codigo");
}

void mostrar(const char* linea1, const char* linea2) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(linea1);
  lcd.setCursor(0, 1); lcd.print(linea2);
}
