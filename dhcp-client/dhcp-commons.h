#ifndef NET_COMMONS_H
#define NET_COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define PUERTO_SERVIDOR_DHCP 67
#define PUERTO_CLIENTE_DHCP 68
#define TAMANO_CHADDR 16
#define TAMANO_SNAME  64
#define TAMANO_FILE   128

struct paquete_dhcp {
  uint8_t  op;
  uint8_t  htype;
  uint8_t  hlen;
  uint8_t  hops;
  uint32_t xid;
  uint16_t secs;
  uint16_t flags;
  uint32_t ciaddr;
  uint32_t yiaddr;
  uint32_t siaddr;
  uint32_t giaddr;
  uint8_t  chaddr[TAMANO_CHADDR];
  char     sname[TAMANO_SNAME];
  char     file[TAMANO_FILE];
  uint32_t magic_cookie;
  uint8_t opciones[312];
};

int obtener_mac(const char *interfaz, uint8_t *direccion_mac);
int enviar_broadcast_socket(struct paquete_dhcp *paquete);
int recibir_broadcast_socket(int descriptor_socket, struct paquete_dhcp *respuesta);
void imprimir_ip(uint32_t ip);
void analizar_opciones(uint8_t *opciones, int tamano);
void imprimir_respuesta_dhcp(struct paquete_dhcp *paquete);

#endif // NET_COMMONS_H
