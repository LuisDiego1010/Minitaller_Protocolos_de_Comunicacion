# Misión 2: La cerradura (UART)

[← Volver al taller](../README.md) · **Anterior:** [Misión 1 (I2C)](../1-sensor-i2c/) · **Siguiente:** [Misión 3 (SSH)](../3-servidor-ssh/)

**Circuito:** [Cerradura UART](https://www.tinkercad.com/things/9p5PZjDOg6O-tutorial-la-cerradura-uart?sharecode=QP0IS_wcJ5oSPeA_5rUCfEBoJbjdjMOru3XohE7zV8Y)

> Abrí el circuito y hacé **Copiar y modificar** para trabajar en tu propia copia; si no, no vas a poder editar el código. ¿Primera vez con Tinkercad? Mirá [cómo usarlo](../README.md#antes-de-empezar-cómo-usar-tinkercad).

## El sistema

El **Lector** tiene un teclado y le envía por UART el código tecleado a la **Puerta**, que tiene LEDs, un zumbador y una pantalla. El circuito ya está armado; vos lo programás en 5 etapas. En cada una, **reemplazás** el código de una placa por el de la etapa.

> **El código de la cerradura es `1958`.** Andrea lo eligió porque es el año en que Jack Kilby, en Texas Instruments, demostró el primer circuito integrado: el antepasado de cada chip que usás en este taller, desde el Arduino hasta la pantalla.

![Circuito de la cerradura](../../img/circuito-uart.png)

Antes de empezar, fijate en dos detalles del cableado: los cables de UART van **cruzados** (el TX del Lector, pin ~11, va al RX de la Puerta, pin ~10, y viceversa), y las dos placas comparten **GND**.

**El ciclo de cada etapa es siempre el mismo:**

1. **Detené la simulación.** Tinkercad no aplica los cambios de código mientras corre.
2. En el desplegable de arriba, elegí la placa que toca y pegá el código.
3. **Iniciá la simulación** y abrí el **Monitor en serie** de esa misma placa.
4. Probá y compará con el resultado esperado.

El desplegable manda sobre las dos cosas: qué código editás y qué monitor ves. Tinkercad muestra **un solo monitor a la vez**, el de la placa seleccionada.

## Etapa 1 — Lector: leer el teclado

Elegí el **Lector** (Arduino de la izquierda) y pegá este código.

<details>
<summary>Ver el código</summary>

```cpp
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
```

</details>

El teclado es una **matriz** de 4×4: cada tecla une una fila con una columna, y la librería `Keypad` detecta cuál.

**Iniciá la simulación** y abrí el monitor del Lector. Debería aparecer `Lector listo. Presiona teclas.`

**Resultado:** al presionar teclas en el teclado del circuito, el monitor muestra `Tecla: 1`, `Tecla: 9`...

## Etapa 2 — Lector: enviar por UART

**Detené la simulación** y reemplazá el código del **Lector** por este.

<details>
<summary>Ver el código</summary>

```cpp
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
```

</details>

- `SoftwareSerial uart(10, 11)` crea un UART en los pines ~10 y ~11, porque los pines 0 y 1 los usa el monitor serie.
- `BAUD_UART = 1200` es la velocidad. UART no tiene reloj compartido, así que **los dos lados deben usar la misma**.
- Al presionar `#`, envía el código seguido de `'\n'`, que marca el fin del mensaje.

**Iniciá la simulación** y tecleá `1958#` en el teclado.

**Resultado:** el monitor del Lector muestra `-> enviado: 1958`.

Por ahora nadie escucha del otro lado: la Puerta todavía no tiene código.

## Etapa 3 — Puerta: recibir

**Detené la simulación.** En el desplegable, cambiá a la **Puerta** (Arduino de la derecha) y pegá este código.

<details>
<summary>Ver el código</summary>

```cpp
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
```

</details>

La Puerta escucha en el mismo UART, a la misma velocidad, y muestra cada byte que llega.

**Iniciá la simulación.** De acá en adelante vas a mirar el monitor de la **Puerta**: dejá esa placa seleccionada en el desplegable, aunque tecleés en el teclado del Lector.

**Resultado:** al teclear `1958#`, el monitor de la Puerta muestra `1958`. El mensaje viajó de una placa a la otra.

![Puerta recibiendo](../../img/uart-etapa3-recepcion.png)

## Etapa 4 — Puerta: verificar el código

**Detené la simulación** y reemplazá el código de la **Puerta** por este.

<details>
<summary>Ver el código</summary>

```cpp
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
```

</details>

La Puerta arma el mensaje byte por byte hasta recibir `'\n'`, y lo compara con el código correcto usando `strcmp()`.

**Iniciá la simulación** y probá los dos casos.

**Resultado:** `1234#` muestra `Codigo invalido`; `1958#` muestra `PUERTA ABIERTA` y enciende el LED verde.

## Etapa 5 — Puerta: versión completa

**Detené la simulación** y reemplazá el código de la **Puerta** por este.

<details>
<summary>Ver el código</summary>

```cpp
// ETAPA 5 - PUERTA: version completa con zumbador y pantalla
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const long BAUD_UART = 1200;
const char CODIGO_CORRECTO[] = "1958";

// El fragmento 2 guardado como codigos ASCII (cada byte es una letra)
const byte FRAGMENTO_2[] = {0x74, 0x52, 0x39, 0x77};

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
```

</details>

Agregamos tres cosas: la pantalla por **I2C** —así que en esta placa conviven UART e I2C—, el zumbador y el fragmento 2, guardado como ASCII.

**Iniciá la simulación** y tecleá `1958#`.

**Resultado:** se enciende el LED verde, suena el zumbador y la pantalla muestra `Acceso concedido` y el **fragmento 2**.

**Anotalo tal cual aparece.** Con los dos fragmentos ya podés hacer la misión 3.

![Cerradura abierta](../../img/uart-puerta-abierta.png)

## Solución de problemas

| Problema | Solución |
|---|---|
| El monitor serie no muestra nada | Revisá que la simulación esté **iniciada** y que en el desplegable esté elegido el Arduino correcto. |
| Cambié el código y no pasa nada | Detené la simulación, editá y volvé a iniciarla. |
| Veo el monitor del Lector y no el de la Puerta | Cambiá de placa en el desplegable: Tinkercad muestra un solo monitor a la vez. |
| No puedo editar el código | Te falta **Copiar y modificar**: estás viendo el circuito original, no tu copia. |
| La Puerta no recibe nada | Revisá que los cables de UART estén cruzados, que haya GND común y que ambos códigos usen `BAUD_UART = 1200`. |
| La Puerta recibe caracteres raros | Las velocidades no coinciden: revisá `BAUD_UART` en los dos códigos. |
| `Codigo invalido` con `1958` | Presioná `*` para borrar y volvé a escribirlo. |
| La pantalla no enciende (etapa 5) | En las propiedades de la LCD, el tipo debe ser **PCF8574**. |

---

**Siguiente: [Misión 3: El servidor del laboratorio (SSH)](../3-servidor-ssh/).**