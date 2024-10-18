#include "./dhcp-commons.h"
#include "./dhcp-discover.h"

void gestionar_descubrimiento(int descriptor_servidor, struct paquete_red *solicitud, struct sockaddr *direccion_cliente) {
  struct paquete_red respuesta;
  printf("Procesando descubrimiento de red\n");

  // Crear respuesta de oferta
  memset(&respuesta, 0, sizeof(struct paquete_red));

  respuesta.op = 2; // Boot Reply
  respuesta.htype = 1; // Ethernet
  respuesta.hlen = 6; // Longitud de la MAC
  respuesta.xid = solicitud->xid; // Debe coincidir con el xid de la solicitud
  respuesta.yiaddr = inet_addr("192.168.1.100"); // IP ofrecida
  respuesta.siaddr = inet_addr("192.168.1.1"); // IP del servidor

  int desplazamiento = 0;
  uint32_t mascara_red = inet_addr("255.255.255.0");
  uint32_t enrutador = inet_addr("192.168.1.1");
  uint32_t servidor_dns = inet_addr("8.8.8.8");
  uint8_t tiempo_concesion[] = {0x00, 0x01, 0x51, 0x80}; // 86400 segundos (1 día)
  char dominio[] = "ejemplo.com";

  // Opciones de red
  agregar_opcion(respuesta.opciones, &desplazamiento, 53, 1, "\x02"); // DHCPOFFER
  agregar_opcion(respuesta.opciones, &desplazamiento, 1, 4, &mascara_red); // Máscara de subred
  agregar_opcion(respuesta.opciones, &desplazamiento, 3, 4, &enrutador); // Enrutador
  agregar_opcion(respuesta.opciones, &desplazamiento, 6, 4, &servidor_dns); // Servidor DNS
  agregar_opcion(respuesta.opciones, &desplazamiento, 51, 4, tiempo_concesion); // Tiempo de concesión
  agregar_opcion(respuesta.opciones, &desplazamiento, 15, strlen(dominio), dominio); // Nombre de dominio
  agregar_opcion(respuesta.opciones, &desplazamiento, 255, 0, NULL); // Fin de opciones

  // Enviar la respuesta de oferta
  sendto(descriptor_servidor, &respuesta, sizeof(respuesta), 0, direccion_cliente, sizeof(*direccion_cliente));

  printf("Oferta de red enviada\n");
}
