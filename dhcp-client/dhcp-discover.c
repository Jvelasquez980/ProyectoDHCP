#include "./dhcp-commons.h"


int enviar_descubrimiento_dhcp(char *ip_ofrecida) {
  uint8_t direccion_mac[6];
  struct paquete_dhcp paquete, respuesta;
  memset(&paquete, 0, sizeof(paquete));

  if (obtener_mac("enp0s3", direccion_mac) < 0) {
    printf("Error al obtener la dirección MAC\n");
    return -1;
  }

  paquete.op = 1; // BOOTREQUEST
  paquete.htype = 1; // Ethernet
  paquete.hlen = 6; // Longitud de la dirección MAC
  paquete.xid = htonl(random()); // ID de transacción
  paquete.flags = htons(0x8000); // Set broadcast flag
  memcpy(paquete.chaddr, direccion_mac, 6);

  uint8_t *opciones = paquete.opciones;
  *opciones++ = 53;
  *opciones++ = 1;
  *opciones++ = 1;
  *opciones++ = 55;
  *opciones++ = 4;
  *opciones++ = 1;
  *opciones++ = 3;
  *opciones++ = 6;
  *opciones++ = 15;
  *opciones++ = 255;

  int sock = enviar_broadcast_socket(&paquete);
  printf("DHCPDISCOVER enviado como broadcast\n");

  int valread = recibir_broadcast_socket(sock, &respuesta);
  if (valread > 0) {
    imprimir_respuesta_dhcp(&respuesta);
    const char *ip_str = inet_ntoa(*(struct in_addr *)&paquete.yiaddr);
    strcpy(ip_ofrecida, ip_str);
  } else {
    printf("Error al recibir DHCPOFFER\n");
  }

  close(sock);
  return 0;
}
