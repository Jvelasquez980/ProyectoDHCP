#ifndef DHCP_COMMONS_H
#define DHCP_COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Estructura simplificada de un paquete DHCP
struct paquete_red {
  uint8_t op;         // Tipo de mensaje (1 = request, 2 = reply)
  uint8_t htype;      // Tipo de hardware (1 = Ethernet)
  uint8_t hlen;       // Longitud de la dirección de hardware
  uint8_t hops;       // Saltos
  uint32_t xid;       // ID de transacción
  uint16_t secs;      // Segundos transcurridos
  uint16_t flags;     // Flags
  uint32_t ciaddr;    // IP del cliente
  uint32_t yiaddr;    // IP 'your' (ofrecida)
  uint32_t siaddr;    // IP del servidor
  uint32_t giaddr;    // IP del gateway
  uint8_t chaddr[16]; // Dirección de hardware del cliente
  uint8_t sname[64];  // Nombre del servidor
  uint8_t file[128];  // Nombre del archivo de boot
  uint32_t magic_cookie;
  uint8_t opciones[64];// Opciones DHCP
};

void agregar_opcion(uint8_t *opciones, int *desplazamiento, uint8_t codigo, uint8_t longitud, void *dato);

#endif // NET_UTILS_H
