# Misión 1: El sensor de temperatura (I2C)

[← Volver al taller](../README.md). **Siguiente:** [Misión 2 (UART)](../2-cerradura-uart/)

**Circuito:** [Monitoreo de temperatura](https://www.tinkercad.com/things/4u4fEo53Gir-tutorial-monitoreotemperatura?sharecode=hO4WPVOret15NkqS5hze6cnsi79mzYAGFILFfxE1k_k)

> ¿Primera vez con Tinkercad? Mirá [cómo usarlo](../README.md#antes-de-empezar-cómo-usar-tinkercad) antes de seguir.

## El sistema

Es el sistema de la demostración, pero con la **regla de emergencia** de Andrea: tres Arduino y una pantalla en un mismo bus I2C.

| Dispositivo | Dirección | Función |
|---|---|---|
| Maestro | — | Cada segundo pide la temperatura y la reenvía |
| Esclavo 1 | `0x08` | Lee el sensor TMP36 |
| Esclavo 2 | `0x09` | Pantalla, 5 LEDs y alarma |
| Pantalla LCD | `0x20` | Muestra la temperatura |

![Circuito de la misión 1](../../img/demo-circuito.png)

**¿Por qué un incendio libera la clave?** Por normas de seguridad, los sistemas de control de acceso liberan las cerraduras cuando se activa la alarma de incendio, para que nadie quede atrapado y puedan entrar los bomberos. Vos no vas a incendiar nada: vas a **simular** la emergencia subiendo la temperatura que lee el sensor. Y como un sensor se puede engañar, Andrea solo le confió la mitad de la clave.

## Paso 1.1: Iniciá la simulación

Iniciá la simulación y abrí el monitor del **maestro**. Cada segundo vas a ver:

```
[Master] Temperatura recibida: 22.30 °C
[Master] Dato enviado al Slave 2 OK
```

La primera línea indica que el esclavo 1 respondió; la segunda, que el esclavo 2 confirmó con **ACK**.

## Paso 1.2: Subí la temperatura

Hacé clic en el sensor TMP36 y subí la temperatura con el control deslizante. La barra de LEDs se llena:

| Temperatura | < 25 °C | 25–34,9 °C | 35–44,9 °C | 45–56,9 °C | ≥ 57 °C |
|---|---|---|---|---|---|
| LEDs | 1 | 2 | 3 | 4 | 5 + alarma |

![Control de temperatura](../../img/i2c-control-temperatura.png)

## Paso 1.3: Activá la emergencia

Llevá la temperatura a **57 °C o más**, la temperatura a la que se activan los detectores de calor de los edificios. Suena la alarma y la pantalla muestra `ALERTA INCENDIO` y el **fragmento 1**.

**Anotalo tal cual aparece**, respetando mayúsculas y símbolos. Lo vas a necesitar en la misión 3.

![Fragmento 1](../../img/i2c-fragmento-1.png)

> Nota: la captura del código está difuminada para que hagas el proceso por tu cuenta y no te saltees la parte práctica.

> **En el código:** la alarma usa `millis()` en lugar de `delay()`, para que el Arduino siga atendiendo el bus I2C mientras suena. Y el fragmento está guardado como códigos ASCII (`0x4B, 0x76...`): así viajan las letras por cualquier protocolo, como bytes.

## Solución de problemas

| Problema | Solución |
|---|---|
| El monitor serie no muestra nada | Revisá en el desplegable que sea el Arduino correcto y que la simulación esté iniciada. |
| Cambié el código y no pasa nada | Detené la simulación, editá y volvé a iniciarla. |
| La pantalla no enciende | En las propiedades de la LCD, el tipo debe ser **PCF8574**. |
| El fragmento 1 no aparece | Hace falta llegar a **57 °C o más**; esperá uno o dos segundos. |

---

**Siguiente: [Misión 2: La cerradura (UART)](../2-cerradura-uart/).**