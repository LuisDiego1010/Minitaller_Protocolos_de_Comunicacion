# Mini-Taller: Protocolos de comunicación de bajo y alto nivel

**EL5841 Taller de Sistemas Embebidos** · Instituto Tecnológico de Costa Rica · II Semestre 2026
**Diseñado por:** Luis Diego García Rojas

Bienvenido al repositorio del mini-taller sobre protocolos de comunicación. Recorremos el camino de un dato desde los cables hasta la red: primero los protocolos que comunican chips dentro de una placa (**UART, SPI, I2C y JTAG**) y después los que comunican sistemas a través de internet (**SSH y MQTT**), siguiendo el modelo OSI.

La parte práctica es una misión: el laboratorio quedó cerrado y, para abrirlo, hay que comunicarse con tres dispositivos, cada uno en su propio protocolo.

![Portada](img/portada.jpeg)

## Estructura del repositorio

El repositorio separa el material del expositor del material de los estudiantes, igual que la dinámica de la clase:

```
Minitaller_Protocolos_de_Comunicacion/
├── img/
├── demostracion/
│   └── README.md
├── presentacion/
│   └── Presentacion.pdf
├── taller-estudiantes/
│   ├── README.md 
│   ├── 1-sensor-i2c/
│   ├── 2-cerradura-uart/
│   │   └── etapas/
│   └── 3-servidor-ssh/
│       ├── README.md
│       ├── docker-compose.yml
│       └── servidor/
├── README.md
```

## Dinámica del taller

| Actividad | Tiempo | Descripción |
|---|---|---|
| Rompehielos: Gartic Phone | 15 min | Un "teléfono descompuesto" con dibujos: un mensaje pasa por toda la clase y llega deformado. Plantea el problema que resuelven los protocolos. |
| Presentación | 25 min | Modelo OSI, protocolos de bajo nivel, transición a la red y protocolos de alto nivel, con espacio para preguntas. |
| Demostración | 15 min | El monitoreo de temperatura por I2C, en vivo, como introducción al tutorial (ver [`demostracion/`](demostracion/)). |
| Tutorial guiado | 30–45 min | Las tres misiones del laboratorio cerrado (ver [`taller-estudiantes/`](taller-estudiantes/)). |
| Cierre: Kahoot | 7–8 min | Seis casos prácticos: elegir el protocolo más adecuado para cada situación. |

### 1. Rompehielos (Gartic Phone)

En https://garticphone.com se crea una sala en modo Normal, con los turnos reducidos para que dure unos 10-15 minutos. Cada persona escribe una frase, la siguiente la dibuja, otra adivina el dibujo, y así sucesivamente.

Al final se muestran las cadenas y se cierra con la idea: la comunicación funciona mejor cuando hay un lenguaje común y reglas claras para interpretar lo que se transmite.

### 2. Demostración (`demostracion/`)

Se muestra un sistema de monitoreo de temperatura con cuatro dispositivos en un mismo bus I2C: tres Arduino y una pantalla LCD, simulados en Tinkercad. Se ve en vivo el direccionamiento, la confirmación con ACK y las resistencias pull-up. Al superar los 30 °C, suena una alarma, como en un sistema real de monitoreo.

**El circuito, el código y el guion de la demostración están en [`demostracion/README.md`](demostracion/README.md).**

### 3. Tutorial guiado (`taller-estudiantes/`)

> Un corte de luz reinició el sistema de control de acceso del laboratorio en modo seguro, y la puerta quedó bloqueada. La contraseña del servidor que lo administra se dividió en dos fragmentos, y cada uno lo guarda un dispositivo que habla un protocolo distinto.

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
git clone https://github.com/LuisDiego1010/Minitaller_Protocolos_de_Comunicacion.git
cd Minitaller_Protocolos_de_Comunicacion
```

Y seguí directamente la guía paso a paso en [`taller-estudiantes/README.md`](taller-estudiantes/README.md).

## Recursos adicionales

- Presentación: [`Garcia_Protocolos_Presentacion.pdf`](presentacion/Garcia_Protocolos_Presentacion.pdf)
- Demostración: [`demostracion/README.md`](demostracion/README.md)
- Circuito de la misión 1 en Tinkercad: [Monitoreo de temperatura](https://www.tinkercad.com/things/4u4fEo53Gir-tutorial-monitoreotemperatura?sharecode=hO4WPVOret15NkqS5hze6cnsi79mzYAGFILFfxE1k_k)
- Circuito de la misión 2 en Tinkercad: [Cerradura UART](https://www.tinkercad.com/things/9p5PZjDOg6O-tutorial-la-cerradura-uart?sharecode=QP0IS_wcJ5oSPeA_5rUCfEBoJbjdjMOru3XohE7zV8Y)