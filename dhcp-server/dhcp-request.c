#include "./dhcp-commons.h"
#include "./dhcp-request.h"

void gestionar_solicitud(int descriptor_servidor, struct paquete_red *solicitud, struct sockaddr *direccion_cliente) {
  struct paquete_red respuesta;
  printf("Procesando solicitud de red\n");

  memset(&respuesta, 0, sizeof(struct paquete_red));

  // Copiar campos relevantes de la solicitud
  respuesta.op = 2; // Boot Reply
  respuesta.htype = solicitud->htype;
  respuesta.hlen = solicitud->hlen;
  respuesta.xid = solicitud->xid;
  memcpy(respuesta.chaddr, solicitud->chaddr, 16);

  // Asignar una dirección IP (ejemplo: 192.168.1.100)
  respuesta.yiaddr = inet_addr("192.168.1.100"); // IP ofrecida
  respuesta.siaddr = inet_addr("192.168.1.34"); // IP del servidor

  int desplazamiento = 0;
  uint32_t mascara_red = inet_addr("255.255.255.0");
  uint32_t enrutador = inet_addr("192.168.1.34");
  uint32_t servidor_dns = inet_addr("8.8.8.8");
  uint8_t tiempo_concesion[] = {0x00, 0x01, 0x51, 0x80}; // 86400 segundos (1 día)
  char dominio[] = "uribetequieromucho.com";

  // Opciones de red
  agregar_opcion(respuesta.opciones, &desplazamiento, 53, 1, "\x05"); // DHCPACK
  agregar_opcion(respuesta.opciones, &desplazamiento, 1, 4, &mascara_red); // Máscara de subred
  agregar_opcion(respuesta.opciones, &desplazamiento, 3, 4, &enrutador); // Enrutador
  agregar_opcion(respuesta.opciones, &desplazamiento, 6, 4, &servidor_dns); // Servidor DNS
  agregar_opcion(respuesta.opciones, &desplazamiento, 51, 4, tiempo_concesion); // Tiempo de concesión
  agregar_opcion(respuesta.opciones, &desplazamiento, 15, strlen(dominio), dominio); // Nombre de dominio
  agregar_opcion(respuesta.opciones, &desplazamiento, 255, 0, NULL); // Fin de opciones

  // Enviar respuesta de confirmación
  sendto(descriptor_servidor, &respuesta, sizeof(respuesta), 0, direccion_cliente, sizeof(*direccion_cliente));
  printf("Confirmación de red enviada\n");
}
