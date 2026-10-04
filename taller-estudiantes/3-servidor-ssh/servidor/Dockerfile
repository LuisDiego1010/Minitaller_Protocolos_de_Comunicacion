# Partimos de un Ubuntu minimo
FROM ubuntu:24.04

# Instalamos el servidor SSH. Al instalarlo se generan las
# llaves de host: la identidad (y la huella) del servidor.
RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends openssh-server \
 && rm -rf /var/lib/apt/lists/* \
 && mkdir -p /run/sshd \
 && sed -i 's/^session.*pam_motd.so/#&/' /etc/pam.d/sshd

# Copiamos nuestros archivos al servidor
COPY sshd_lab.conf /etc/ssh/sshd_config.d/lab.conf
COPY puerta /usr/local/bin/puerta
COPY setup.sh /opt/lab/setup.sh

# Preparamos el laboratorio
RUN chmod 755 /usr/local/bin/puerta && bash /opt/lab/setup.sh

# Al arrancar, el servidor SSH queda escuchando
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D", "-e"]
