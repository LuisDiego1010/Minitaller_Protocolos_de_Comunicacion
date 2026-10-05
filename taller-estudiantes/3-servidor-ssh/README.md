# Misión 3: El servidor del laboratorio (SSH)

[← Volver al taller](../README.md) · **Anterior:** [Misión 2 (UART)](../2-cerradura-uart/)

> **Necesitás los dos fragmentos** de las misiones 1 y 2 antes de empezar.

Vas a encender el servidor del laboratorio, una pequeña máquina Linux que corre dentro de tu computadora con Docker, y entrar a él por SSH para abrir la puerta.

Todos los comandos se copian y pegan tal cual. Arriba de cada bloque dice **dónde** se ejecuta:
- 💻 **En tu computadora:** en una terminal normal.
- 🖥️ **En el servidor:** después de conectarte por SSH, en el paso 3.4.

## Paso 3.1: Verificá que tenés Docker

💻 **En tu computadora:**

```bash
docker --version
docker compose version
```

**Deberías ver** dos líneas con números de versión, algo como `Docker version 27.x` y `Docker Compose version v2.x`.

<details>
<summary>¿Te aparece "command not found"? Instalá Docker así (Ubuntu)</summary>

💻 **En tu computadora:**

```bash
sudo apt update
sudo apt install -y docker.io docker-compose-v2
sudo usermod -aG docker $USER
newgrp docker
```

La última línea te permite usar Docker sin `sudo` en esa terminal. Después, volvé a correr los dos comandos de verificación.

En otras distribuciones, seguí la [documentación oficial de Docker](https://docs.docker.com/engine/install/).

</details>

## Paso 3.2: Entrá a la carpeta del servidor

El servidor ya viene en el repositorio.

**Si todavía no lo descargaste**, clonalo:

💻 **En tu computadora:**

```bash
git clone https://github.com/LuisDiego1010/Minitaller_Protocolos_de_Comunicacion.git
cd Minitaller_Protocolos_de_Comunicacion/taller-estudiantes/3-servidor-ssh
```

**Si ya lo tenías clonado**, no lo clonés de nuevo (daría el error `already exists`). Entrá desde donde lo tengas:

```bash
cd ruta/donde/lo/tenés/Minitaller_Protocolos_de_Comunicacion/taller-estudiantes/3-servidor-ssh
```

Comprobá que estás en el lugar correcto:

```bash
ls
```

**Deberías ver:** `docker-compose.yml`, `README.md` y la carpeta `servidor`.

### ¿Qué hay en esta carpeta?

No tenés que modificar nada, pero vale la pena saber qué hace cada archivo:

| Archivo | Qué hace |
|---|---|
| [`docker-compose.yml`](docker-compose.yml) | Crea el servidor y conecta el puerto **2222** de tu computadora con el puerto **22** (SSH) del servidor. |
| [`servidor/Dockerfile`](servidor/Dockerfile) | La "receta" del servidor: un Ubuntu con el servidor SSH instalado. Al instalarse, SSH genera la **identidad** del servidor. |
| [`servidor/sshd_lab.conf`](servidor/sshd_lab.conf) | Configura SSH. Por ejemplo, impide entrar directamente como administrador (`root`). |
| [`servidor/setup.sh`](servidor/setup.sh) | Prepara el laboratorio: crea el usuario `tecnico`, los registros de anoche y la misión. |
| [`servidor/puerta`](servidor/puerta) | El comando que abre la puerta a distancia. |
| `README.md` | Esta guía. |

> **Un detalle de `setup.sh`:** si lo abrís, vas a ver que la contraseña **no está escrita**. Solo aparece su **hash**, una especie de huella de la contraseña. Linux nunca guarda las contraseñas, solo sus hashes: cuando escribís la contraseña, calcula el hash y lo compara. Por eso, aunque tengas el archivo, no podés saber la clave sin los dos fragmentos.

## Paso 3.3: Encendé el servidor

💻 **En tu computadora** (dentro de la carpeta `3-servidor-ssh`):

```bash
docker compose up -d --build
```

La primera vez tarda unos minutos, porque descarga Ubuntu e instala el servidor SSH. Cuando termine, comprobá que está corriendo:

```bash
docker compose ps
```

**Deberías ver** una línea con el servidor en estado `Up` (o `running`).

## Paso 3.4: Conectate por SSH

💻 **En tu computadora:**

```bash
ssh -p 2222 tecnico@localhost
```

Esto le dice a SSH: *"conectate como el usuario `tecnico` a esta misma computadora (`localhost`), por el puerto 2222"*.

**1. La huella del servidor.** La primera vez, SSH te muestra algo así:

```console
usuario@pc:~$ ssh -p 2222 tecnico@localhost
The authenticity of host '[localhost]:2222 ([127.0.0.1]:2222)' can't be established.
ED25519 key fingerprint is SHA256:3A1dLx2QmZ4p8sK7eP4kQ9rT0vJ3wH6bN1m5cY9uR0M.
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

Es la **identidad** del servidor. Como es la primera vez que te conectás, SSH no tiene con qué compararla. Escribí `yes` (la palabra completa) y presioná Enter: SSH la guarda y, desde ahora, la verifica sola en cada conexión. Si algún día cambiara sin motivo, podría ser otra máquina haciéndose pasar por el servidor.

**2. La contraseña.** Son **los dos fragmentos juntos, sin espacios**: primero el fragmento 1 y después el fragmento 2.

- Mientras la escribís **no aparece nada en pantalla**, ni asteriscos. Es normal.
- **Distingue mayúsculas de minúsculas**: escribila con cuidado.
- Si te equivocás, SSH te deja reintentar. Después de 3 intentos fallidos corta la conexión: volvé a correr el comando `ssh`.

**Deberías ver** el mensaje de bienvenida del servidor:

```console
usuario@pc:~$ ssh -p 2222 tecnico@localhost
tecnico@localhost's password:

  =====================================================
   SERVIDOR DEL LABORATORIO DE SISTEMAS EMBEBIDOS
   Modo seguro activo. Puerta del laboratorio: BLOQUEADA
  =====================================================
   Lee tu mision:  cat LEEME.txt

tecnico@servidor-lab:~$
```

## Paso 3.5: Cumplí la misión

Ya estás dentro del servidor. Fijate que la terminal ahora empieza con `tecnico@servidor-lab`: eso indica que los comandos se ejecutan **en el servidor**, no en tu computadora. Ejecutá estos comandos uno por uno.

🖥️ **En el servidor:**

Leé la misión que te dejó Andrea:

```bash
cat LEEME.txt
```

Revisá los registros para ver qué pasó anoche:

```bash
cat /var/log/laboratorio/acceso.log
```

Abrí la puerta del laboratorio a distancia:

```bash
puerta abrir
```

**Deberías ver** la puerta abriéndose y el mensaje `Se genero el acta de recuperacion`.

Revisar registros y ejecutar comandos a distancia son los usos más comunes de SSH: así se administra, por ejemplo, una Raspberry Pi que no tiene monitor ni teclado.

Ahora salí del servidor:

```bash
exit
```

La terminal vuelve a mostrar el nombre de tu computadora.

## Paso 3.6: Descargá el acta con `scp`

`scp` copia archivos entre computadoras a través de SSH, de forma cifrada. Se ejecuta **en tu computadora**, porque es ahí adonde va a llegar el archivo.

💻 **En tu computadora:**

```bash
scp -P 2222 tecnico@localhost:acta_recuperacion.txt .
```

Te va a pedir **la misma contraseña** otra vez. El `.` del final significa *"guardalo en la carpeta donde estoy"*.

> Ojo: en `scp` el puerto va con **`-P` mayúscula**, a diferencia de `ssh`, que usa `-p` minúscula.

Abrí el acta:

```bash
cat acta_recuperacion.txt
```

**Deberías ver** el acta de recuperación, con tu **código de finalización** y un último mensaje de Andrea. Tu código va a ser distinto al del ejemplo:

```console
usuario@pc:~$ cat acta_recuperacion.txt
=======================================================
          ACTA DE RECUPERACION DEL LABORATORIO
=======================================================
Fecha: AAAA-MM-DD HH:MM
Codigo de finalizacion: LAB-XXXXXX

Que paso:
  Un corte de electricidad reinicio el sistema en modo
  seguro. La puerta se bloqueo y la contrasena del
  servidor quedo dividida en dos fragmentos.

Como se recupero:
  1. I2C: el sensor revelo el fragmento 1 al llegar a 57 C.
  2. UART: se programo el lector y la cerradura, y la
     cerradura revelo el fragmento 2.
  3. SSH: se construyo el servidor, se entro con los dos
     fragmentos, se revisaron los registros y se abrio
     la puerta a distancia.

-------------------------------------------------------
Un ultimo mensaje de Andrea:

  "Lo lograron porque le hablaron a cada dispositivo en
   su protocolo: I2C al sensor, UART a la cerradura y SSH
   al servidor. Si uno solo fallaba, la puerta seguia
   cerrada.

   Y recuerden: ningun protocolo es mas seguro que quien
   lo usa.
     - Cambien siempre las contrasenas de fabrica.
     - Verifiquen la huella del servidor la primera vez.
     - Nunca ignoren la advertencia de huella cambiada.
     - Usen llaves en vez de contrasenas, y nunca
       compartan la llave privada.
     - Copien archivos por canales cifrados (scp, sftp)."
=======================================================
```

## Paso 3.7: Apagá el servidor

💻 **En tu computadora:**

```bash
docker compose down
```

Esto apaga el servidor. Si además querés liberar el espacio que ocupa la imagen descargada:

```bash
docker compose down --rmi local
```

## Solución de problemas

| Problema | Solución |
|---|---|
| `permission denied` al usar Docker | Corré `sudo usermod -aG docker $USER` y después `newgrp docker`. |
| `no configuration file provided` | No estás en la carpeta correcta. Volvé al paso 3.2. |
| `destination path ... already exists` al clonar | Ya tenías el repositorio. No clonés de nuevo: entrá a la carpeta con `cd` (paso 3.2). |
| `Connection refused` | El servidor está apagado. Volvé al paso 3.3. |
| `Permission denied, please try again` al entrar por SSH | La contraseña no es correcta. Revisá los dos fragmentos: juntos, sin espacios, fragmento 1 primero, respetando mayúsculas y minúsculas. |
| SSH cortó la conexión después de varios intentos | Es normal tras 3 contraseñas incorrectas. Volvé a correr `ssh -p 2222 tecnico@localhost`. |
| `scp` dice `Connection refused` o se conecta al puerto 22 | Usaste `-p` minúscula. En `scp` el puerto va con **`-P` mayúscula**. |
| `scp` dice `No such file or directory` | Todavía no generaste el acta. Entrá por SSH y corré `puerta abrir` (paso 3.5). |
| `REMOTE HOST IDENTIFICATION HAS CHANGED` | Reconstruiste el servidor y cambió su huella. Como sabés por qué, es seguro borrar la vieja con `ssh-keygen -R '[localhost]:2222'` y volver a conectarte. |

---

**Terminaste.** Revisá [qué hay que entregar](../README.md#entrega).