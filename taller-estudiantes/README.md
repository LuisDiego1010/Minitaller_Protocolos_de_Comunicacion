# Laboratorio cerrado

**Mini-Taller de Protocolos de Comunicación** · EL5841 Taller de Sistemas Embebidos · Duración: 45 a 60 minutos

## La situación

Andrea, la asistente que diseñó el sistema de control de acceso del laboratorio, lo dejó preparado para cualquier falla. Anoche, un corte de luz lo reinició en **modo seguro**: la puerta quedó bloqueada y la contraseña del servidor que lo administra se dividió en **dos fragmentos**, cada uno guardado en un dispositivo que habla un protocolo distinto.

Esta técnica se llama **control dual**: ningún dispositivo, por sí solo, puede abrir todo.

## Las misiones

| # | Misión | Dispositivo | Protocolo | Resultado |
|---|---|---|---|---|
| 1 | [El sensor de temperatura](1-sensor-i2c/) | Sensor TMP36 | I2C | Fragmento 1 |
| 2 | [La cerradura](2-cerradura-uart/) | Teclado y cerradura | UART | Fragmento 2 |
| 3 | [El servidor del laboratorio](3-servidor-ssh/) | Servidor Linux | SSH | Puerta abierta |

Hacelas **en orden**: la misión 3 necesita los dos fragmentos que te dan las dos primeras.

> **Anotá cada fragmento apenas aparezca.** Respetá mayúsculas, minúsculas y símbolos exactamente como los ves en pantalla. Un error de transcripción acá no se nota hasta la misión 3, y ahí es difícil saber de dónde vino.

## Objetivos

Al terminar vas a saber:

1. Cómo varios dispositivos comparten un bus **I2C** usando direcciones y confirmaciones (ACK).
2. Cómo programar una comunicación **UART** entre dos microcontroladores.
3. Cómo viajan los datos como **bytes** y cómo se representan las letras en **ASCII**.
4. Cómo usar **SSH** como un técnico: verificar un servidor, ejecutar comandos a distancia y copiar archivos.

## Requerimientos

| Recurso | Uso |
|---|---|
| Navegador y cuenta gratuita de [Tinkercad](https://www.tinkercad.com) | Misiones 1 y 2 |
| Linux con Docker y Docker Compose | Misión 3 |
| `ssh` y `scp` (incluidos en Linux) | Misión 3 |

No se necesita hardware: los circuitos se simulan en Tinkercad y el servidor corre en tu computadora.

## Antes de empezar: cómo usar Tinkercad

Esto aplica a las misiones 1 y 2.

1. Abrí el enlace del circuito y hacé **Copiar y modificar** para trabajar en tu propia copia.
2. El botón **Código** abre el programa. En el **desplegable** de arriba elegís el Arduino y en **Texto** ves el código.
3. **Monitor en serie**, abajo del panel, muestra los mensajes del Arduino elegido.
4. Detené la simulación antes de cambiar un código: los cambios no se aplican mientras corre.

![Panel de código de Tinkercad](../img/tinkercad-panel-codigo.png)

## La contraseña del servidor

La contraseña de la misión 3 son **los dos fragmentos juntos, sin espacios ni guion**: primero el fragmento 1 (misión 1) y después el fragmento 2 (misión 2). Distingue mayúsculas de minúsculas.

## Entrega

Completaste el tutorial si obtuviste los dos fragmentos, entraste al servidor, abriste la puerta y descargaste el acta.

**Entregá:**

1. El **código de finalización** del acta.
2. Una **captura** del acta abierta en tu computadora.
3. **Una respuesta breve:** La primera vez que te conectaste, SSH te mostró la huella del servidor y te pidió escribir yes. ¿Para qué sirve guardar esa huella, y qué debería hacer un técnico si algún día SSH le avisa que cambió?

## Referencias

- NXP Semiconductors. (2021). *UM10204: I2C-bus specification and user manual* (Rev. 7.0).
- Microchip Technology. *ATmega328P Datasheet*: secciones de USART y TWI (I2C).
- Analog Devices. *TMP35/TMP36/TMP37 Low Voltage Temperature Sensors* (hoja de datos).
- Ylonen, T., & Lonvick, C. (2006). *RFC 4251: The Secure Shell (SSH) Protocol Architecture*. IETF.
- OpenBSD Project. Páginas de manual de OpenSSH: `ssh(1)`, `sshd_config(5)` y `scp(1)`.
- Arduino. Referencia de las librerías `Wire`, `SoftwareSerial` y `Keypad`. https://www.arduino.cc/reference
- Docker. Documentación oficial de Docker Engine y Compose. https://docs.docker.com

---

**Empezá por la [Misión 1: El sensor de temperatura](1-sensor-i2c/).**
