#include "./dhcp-commons.h"

void agregar_opcion(uint8_t *opciones, int *desplazamiento, uint8_t codigo, uint8_t longitud, void *dato) {
    opciones[(*desplazamiento)++] = codigo;
    opciones[(*desplazamiento)++] = longitud;
    memcpy(opciones + *desplazamiento, dato, longitud);
    *desplazamiento += longitud;
}
