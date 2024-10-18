#ifndef DHCP_DISCOVER_H
#define DHCP_DISCOVER_H

void gestionar_descubrimiento(int descriptor_servidor, struct paquete_red *paquete, struct sockaddr *direccion_cliente);


#endif // DHCP_DISCOVER_H
