#include "./dhcp-discover.h"
#include "./dhcp-request.h"

int main() {
  char ip_ofrecida[30];
  enviar_descubrimiento_dhcp(ip_ofrecida);
  enviar_solicitud_dhcp(ip_ofrecida);
  return 0;
}
