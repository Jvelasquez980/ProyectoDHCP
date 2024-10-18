#include "./dhcp-commons.h"
#include "./dhcp-discover.h"
#include "./dhcp-request.h"

#define PUERTO 67 // Puerto estándar de red

int main() {
  int descriptor_servidor;
  struct sockaddr_in direccion;
  struct paquete_red paquete;

  // Crear socket
  if ((descriptor_servidor = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
      perror("Fallo en la creación del socket");
      exit(EXIT_FAILURE);
  }

  direccion.sin_family = AF_INET;
  direccion.sin_addr.s_addr = INADDR_ANY;
  direccion.sin_port = htons(PUERTO);

  // Vincular el socket
  if (bind(descriptor_servidor, (struct sockaddr *)&direccion, sizeof(direccion)) < 0) {
      perror("Fallo en la vinculación");
      exit(EXIT_FAILURE);
  }

  printf("Servidor de red escuchando en el puerto %d...\n", PUERTO);

  while(1) {
    struct sockaddr_in direccion_cliente;
    socklen_t longitud_direccion_cliente = sizeof(direccion_cliente);

    // Recibir solicitud
    int valread = recvfrom(descriptor_servidor, &paquete, sizeof(paquete), 0,
                            (struct sockaddr *)&direccion_cliente, &longitud_direccion_cliente);
    printf("Solicitud de red recibida\n");

    // Determinar el tipo de mensaje
    uint8_t *opciones = paquete.opciones;
    uint8_t tipo_mensaje = 0;
    while (*opciones != 255 && opciones < paquete.opciones + sizeof(paquete.opciones)) {
        if (*opciones == 53 && *(opciones + 1) == 1) {
            tipo_mensaje = *(opciones + 2);
            break;
        }
        opciones += *(opciones + 1) + 2;
    }

    switch(tipo_mensaje) {
      case 1: // DHCPDISCOVER
        gestionar_descubrimiento(descriptor_servidor, &paquete, (struct sockaddr *)&direccion_cliente);
        break;
      case 3: // DHCPREQUEST
        gestionar_solicitud(descriptor_servidor, &paquete, (struct sockaddr *)&direccion_cliente);
        break;
      default:
        printf("Tipo de mensaje no soportado: %d\n", tipo_mensaje);
    }
  }

  return 0;
}
