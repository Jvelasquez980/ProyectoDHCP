#include "./dhcp-commons.h"

int obtener_mac(const char *interfaz, uint8_t *direccion_mac) {
  struct ifreq solicitud_ifr;
  int descriptor_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (descriptor_socket < 0) {
      perror("socket");
      return -1;
  }

  strcpy(solicitud_ifr.ifr_name, interfaz);
  if (ioctl(descriptor_socket, SIOCGIFHWADDR, &solicitud_ifr) < 0) {
      perror("ioctl");
      close(descriptor_socket);
      return -1;
  }

  memcpy(direccion_mac, solicitud_ifr.ifr_hwaddr.sa_data, 6);
  close(descriptor_socket);
  return 0;
}

int enviar_broadcast_socket(struct paquete_dhcp *paquete) {
  int descriptor_socket;
  struct sockaddr_in direccion_servidor, direccion_cliente;

  // Crear socket
  if ((descriptor_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Error en la creación del socket");
    return -1;
  }

  // Configurar socket para broadcast
  int broadcast = 1;
  if (setsockopt(descriptor_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
    perror("Error al configurar socket para broadcast");
    close(descriptor_socket);
    return -1;
  }

  // Configurar dirección del cliente
  memset(&direccion_cliente, 0, sizeof(direccion_cliente));
  direccion_cliente.sin_family = AF_INET;
  direccion_cliente.sin_addr.s_addr = INADDR_ANY;

  // Vincular socket
  if (bind(descriptor_socket, (struct sockaddr *)&direccion_cliente, sizeof(direccion_cliente)) < 0) {
    perror("Error al vincular socket");
    close(descriptor_socket);
    return -1;
  }

  // Configurar dirección del servidor (broadcast)
  memset(&direccion_servidor, 0, sizeof(direccion_servidor));
  direccion_servidor.sin_family = AF_INET;
  direccion_servidor.sin_port = htons(PUERTO_SERVIDOR_DHCP);
  direccion_servidor.sin_addr.s_addr = INADDR_BROADCAST;

  // Enviar DHCPDISCOVER
  if (sendto(descriptor_socket, paquete, sizeof(*paquete), 0, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) < 0) {
    perror("Error al enviar DHCPDISCOVER");
    close(descriptor_socket);
    return -1;
  }

  return descriptor_socket;
}

int recibir_broadcast_socket(int descriptor_socket, struct paquete_dhcp *respuesta) {
  struct sockaddr_in direccion_servidor;
  socklen_t longitud_direccion_servidor = sizeof(direccion_servidor);
  // Recibir solicitud
  int resultado = recvfrom(descriptor_socket, respuesta, sizeof(*respuesta), 0, (struct sockaddr *)&direccion_servidor, &longitud_direccion_servidor);
  return resultado;
}

void imprimir_ip(uint32_t ip) {
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    printf("%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
}

void analizar_opciones(uint8_t *opciones, int tamano) {
  int i = 0;
  while (i < tamano) {
    uint8_t codigo = opciones[i++];
    uint8_t longitud = opciones[i++];

    switch(codigo) {
      case 1: // Máscara de subred
        printf("Máscara de subred: ");
        imprimir_ip(*(uint32_t*)(opciones + i));
        printf("\n");
        break;
      case 3: // Router
        printf("Router: ");
        imprimir_ip(*(uint32_t*)(opciones + i));
        printf("\n");
        break;
      case 6: // Servidor DNS
        printf("Servidor DNS: ");
        imprimir_ip(*(uint32_t*)(opciones + i));
        printf("\n");
        break;
      case 15: // Nombre de dominio
        printf("Nombre de dominio: %.*s\n", longitud, opciones + i);
        break;
      case 51: // Tiempo de concesión
        printf("Tiempo de concesión: %u segundos\n", ntohl(*(uint32_t*)(opciones + i)));
        break;
      case 255: // Fin
        return;
    }
    i += longitud;
  }
}

void imprimir_respuesta_dhcp(struct paquete_dhcp *paquete) {
  printf("RESPUESTA recibida:\n");
  printf("IP ofrecida: %s\n", inet_ntoa(*(struct in_addr *)&paquete->yiaddr));
  printf("IP del servidor: %s\n", inet_ntoa(*(struct in_addr *)&paquete->siaddr));

  // Imprimir opciones DHCP
  if (paquete->opciones[0] == 53 && paquete->opciones[2] == 2) {
    printf("Tipo de mensaje: DHCPOFFER\n");
  }
  if (paquete->opciones[0] == 53 && paquete->opciones[2] == 5) {
    printf("Tipo de mensaje: DHCPACK\n");
  }

  analizar_opciones(paquete->opciones, sizeof(paquete->opciones));
}
