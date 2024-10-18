#ifndef DHCP_REQUEST_H
#define DHCP_REQUEST_H

void gestionar_solicitud(int descriptor_servidor, struct paquete_red *paquete, struct sockaddr *direccion_cliente);


#endif // DHCP_REQUEST_H
