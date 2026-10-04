# Mini-Taller: Protocolos de comunicación de bajo y alto nivel

**EL5841 Taller de Sistemas Embebidos** · Instituto Tecnológico de Costa Rica · II Semestre 2026
**Diseñado por:** Luis Diego García Rojas

Bienvenido al repositorio del mini-taller sobre protocolos de comunicación. Recorremos el camino de un dato desde los cables hasta la red: primero los protocolos que comunican chips dentro de una placa (**UART, SPI, I2C y JTAG**) y después los que comunican sistemas a través de internet (**SSH y MQTT**), siguiendo el modelo OSI.

La parte práctica es una misión: **el laboratorio quedó cerrado** y, para abrirlo, hay que comunicarse con tres dispositivos, cada uno en su propio protocolo.

<!-- IMAGEN OPCIONAL: un banner o una captura de la diapositiva de portada.
![Portada](img/portada.png) -->

## Estructura del repositorio

El repositorio separa el material del expositor del material de los estudiantes, igual que la dinámica de la clase:

```
Mini-Taller-Protocolos/
├── README.md                          <- Este archivo: visión general y dinámica.
├── Garcia_Protocolos_Presentacion.pdf <- Presentación de la sesión.
├── presentacion/
│   └── protocolos.tex                 <- Fuente de la presentación (LaTeX/Beamer).
├── demostracion/                      <- Lo que muestra el expositor en clase.
│   ├── README.md                      <- Guion y cómo correr la demostración.
│   ├── maestro/                       <- Arduino maestro del bus I2C.
│   ├── esclavo1_sensor/               <- Arduino con el sensor TMP36 (0x08).
│   ├── esclavo2_lcd_leds/             <- Arduino con LCD y LEDs (0x09).
│   └── circuito/                      <- Esquemático del circuito.
├── taller-estudiantes/                <- Material del tutorial guiado.
│   ├── README.md                      <- GUÍA COMPLETA DEL TUTORIAL (empezá aquí).
│   ├── 1-sensor-i2c/                  <- Misión 1: el sensor de temperatura.
│   ├── 2-cerradura-uart/etapas/       <- Misión 2: código de la cerradura, por etapas.
│   └── 3-servidor-ssh/                <- Misión 3: archivos del servidor SSH.
├── img/                               <- Imágenes usadas en las guías.
├── .gitignore
└── .gitattributes                     <- Mantiene los scripts con finales de línea de Linux.
```

## Dinámica del taller

La sesión dura entre 95 y 110 minutos y se basa en la estructura del instructivo del curso:

| Actividad | Tiempo | Descripción |
|---|---|---|
| Rompehielos: Gartic Phone | 5 min | Un "teléfono descompuesto" con dibujos: un mensaje pasa por toda la clase y llega deformado. Plantea el problema que resuelven los protocolos. |
| Presentación | 25 min | Modelo OSI, protocolos de bajo nivel, transición a la red y protocolos de alto nivel. |
| Preguntas y comentarios | 15 min | Dudas conceptuales. |
| Demostración | 15 min | El monitoreo de temperatura por I2C, en vivo (ver [`demostracion/`](demostracion/)). |
| Tutorial guiado | 30–45 min | Las tres misiones del laboratorio cerrado (ver [`taller-estudiantes/`](taller-estudiantes/)). |
| Cierre: Kahoot | 7–8 min | Seis casos prácticos: elegir el protocolo más adecuado para cada situación. |

### 1. Rompehielos (Gartic Phone)

En https://garticphone.com se crea una sala en modo **Normal**, con los turnos reducidos para que dure unos 5 minutos. Cada persona escribe una frase, la siguiente la dibuja, otra adivina el dibujo, y así sucesivamente. Conviene pedir frases sobre comunicación entre dispositivos, por ejemplo: *"una Raspberry Pi le avisa a la nube que se abrió la puerta"*.

Al final se muestran las cadenas y se cierra con la idea central: *el mensaje llegó irreconocible porque nadie verificó nada; los protocolos existen para evitarlo*.

### 2. Demostración (`demostracion/`)

El expositor muestra un sistema de monitoreo de temperatura con **cuatro dispositivos en un mismo bus I2C**: tres Arduino y una pantalla LCD, simulados en Tinkercad. Se ven en vivo el direccionamiento, la confirmación con ACK y las resistencias pull-up.

### 3. Tutorial guiado (`taller-estudiantes/`)

> Un corte de luz reinició el sistema de control de acceso del laboratorio en modo seguro, y la puerta quedó bloqueada. La contraseña del servidor que lo administra se dividió en **dos fragmentos**, y cada uno lo guarda un dispositivo que habla un protocolo distinto.

| Misión | Protocolo | Plataforma | Qué se hace | Resultado |
|---|---|---|---|---|
| 1 | I2C | Tinkercad | Usar el sensor de temperatura ya armado | Fragmento 1 |
| 2 | UART | Tinkercad | Programar la cerradura paso a paso, en 5 etapas | Fragmento 2 |
| 3 | SSH | Docker | Construir el servidor archivo por archivo y entrar con los dos fragmentos | Puerta abierta y acta |

**La guía completa, con todos los pasos, el código y las explicaciones, está en [`taller-estudiantes/README.md`](taller-estudiantes/README.md).**

## Requisitos previos

- Navegador web y una cuenta gratuita de [Tinkercad](https://www.tinkercad.com) (misiones 1 y 2).
- Linux (Ubuntu 22.04 o superior recomendado) con **Docker Engine y Compose v2** (misión 3).
- Cliente SSH (incluido en Linux y macOS).

Para ahorrar tiempo en clase, instalá Docker y descargá la imagen base **antes** de la sesión:

```bash
sudo apt update
sudo apt install -y docker.io docker-compose-v2
sudo usermod -aG docker $USER      # Después, cerrá sesión y volvé a entrar
docker pull ubuntu:24.04
```

## Cómo empezar

```bash
git clone <enlace-de-este-repositorio> Mini-Taller-Protocolos
cd Mini-Taller-Protocolos/taller-estudiantes
```

Y seguí la guía de [`taller-estudiantes/README.md`](taller-estudiantes/README.md).

## Recursos adicionales

- Presentación: [`Garcia_Protocolos_Presentacion.pdf`](Garcia_Protocolos_Presentacion.pdf)
- Circuito de la misión 1 en Tinkercad: *(agregar enlace)*
- Circuito de la misión 2 en Tinkercad: *(agregar enlace)*
