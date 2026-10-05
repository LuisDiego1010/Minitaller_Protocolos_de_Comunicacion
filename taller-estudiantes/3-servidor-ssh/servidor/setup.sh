#!/usr/bin/env bash
# Prepara el laboratorio dentro del servidor.
set -e

# 1. El usuario tecnico. Su contrasena no esta escrita aqui:
#    solo guardamos su HASH, igual que Linux en /etc/shadow.
useradd -m -s /bin/bash tecnico
echo 'tecnico:$6$Lab5841sal$Df6WX5eNb683kZPSytWz/xGeI4ntGsbZECyfR4wAou1Ugv4AwwQ98dbuPmnmFCSB4efugQeB2USXrEknUdNK90' | chpasswd -e

# 2. Un codigo de finalizacion al azar, distinto en cada computadora
mkdir -p /opt/lab
echo "LAB-$(tr -dc 'A-Z0-9' < /dev/urandom | head -c 6 || true)" > /opt/lab/codigo
chmod 644 /opt/lab/codigo

# 3. Los registros de lo que paso anoche
mkdir -p /var/log/laboratorio
cat > /var/log/laboratorio/acceso.log <<'LOG'
2026-10-02 18:30:02  cerradura  Acceso concedido (tarjeta 4411)
2026-10-02 19:05:44  cerradura  Puerta cerrada
2026-10-02 22:41:07  energia    CORTE DE ELECTRICIDAD
2026-10-02 22:47:52  energia    Energia restablecida. Reinicio del sistema
2026-10-02 22:47:55  sistema    Modo seguro activado. Puerta BLOQUEADA
2026-10-02 22:47:56  sistema    Contrasena del servidor dividida en dos fragmentos
2026-10-02 22:47:57  sensor     Fragmento 1 resguardado en el sensor de temperatura (I2C)
2026-10-02 22:47:57  cerradura  Fragmento 2 resguardado en la cerradura (UART)
2026-10-03 07:15:02  sistema    Puerta bloqueada. Proyectos finales dentro del laboratorio
LOG
chmod 644 /var/log/laboratorio/acceso.log

# 4. El mensaje que se ve al entrar
cat > /home/tecnico/.bash_profile <<'MSG'
echo
echo "  ====================================================="
echo "   SERVIDOR DEL LABORATORIO DE SISTEMAS EMBEBIDOS"
echo "   Modo seguro activo. Puerta del laboratorio: BLOQUEADA"
echo "  ====================================================="
echo "   Lee tu mision:  cat LEEME.txt"
echo
MSG

# 5. La mision, de parte de Andrea
cat > /home/tecnico/LEEME.txt <<'MISION'
Si estas leyendo esto, lograste entrar. Bien hecho.

Juntaste los dos fragmentos: el del sensor (I2C) y el de la
cerradura (UART). Esa division era a proposito: se llama
control dual, y evita que una sola persona tome el sistema.

Ahora hace lo que haria cualquier tecnico desde aqui:
  1. Revisa los registros:  cat /var/log/laboratorio/acceso.log
  2. Abri la puerta:        puerta abrir
  3. Descarga el acta de recuperacion a TU computadora con scp.

-- Andrea
MISION

chown -R tecnico:tecnico /home/tecnico
