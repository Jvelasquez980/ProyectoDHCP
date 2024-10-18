#include "./dhcp-commons.h"

int enviar_solicitud_dhcp(char* ip_ofrecida) {
  uint8_t direccion_mac[6];
  struct paquete_dhcp paquete, respuesta;
  memset(&paquete, 0, sizeof(paquete));

  if (obtener_mac("enp0s3", direccion_mac) < 0) {
    printf("Error al obtener la dirección MAC\n");
    return -1;
  }

  paquete.op = 1;
  paquete.htype = 1;
  paquete.hlen = 6;
  paquete.xid = htonl(random());
  paquete.flags = htons(0x8000);
  memcpy(paquete.chaddr, direccion_mac, 6);

  uint8_t *puntero_opciones = paquete.opciones;
  *puntero_opciones++ = 53;
  *puntero_opciones++ = 1;
  *puntero_opciones++ = 3;
  *puntero_opciones++ = 61;
  *puntero_opciones++ = 7;
  *puntero_opciones++ = 1;
  memcpy(puntero_opciones, direccion_mac, 6);
  puntero_opciones += 6;
  *puntero_opciones++ = 50;
  *puntero_opciones++ = 4;
  *(uint32_t*)puntero_opciones = inet_addr(ip_ofrecida);
  puntero_opciones += 4;
  *puntero_opciones++ = 255;

  int sock = enviar_broadcast_socket(&paquete);
  printf("DHCPREQUEST enviado como broadcast\n");

  int valread = recibir_broadcast_socket(sock, &respuesta);
  if (valread > 0) {
    imprimir_respuesta_dhcp(&respuesta);
  } else {
    printf("Error al recibir DHCPOFFER\n");
  }

  close(sock);
  return 0;
}
