# ProyectoDHCP

Introducción

Este proyecto tiene como objetivo implementar un servidor DHCP (Dynamic Host Configuration Protocol) utilizando dos máquinas virtuales conectadas a través de VirtualBox. La comunicación entre el servidor DHCP y el cliente se realizará mediante la API de sockets Berkeley, usando el formato de socket SOCK_DGRAM para la transmisión de datos.

Desarrollo

En este entorno, un servidor DHCP alojado en una máquina virtual será el responsable de asignar dinámicamente direcciones IP y otros parámetros de configuración de red a una segunda máquina virtual cliente. A través del protocolo UDP, los mensajes de solicitud y respuesta se enviarán en formato broadcast para asegurar que el cliente pueda recibir la configuración de red de manera automática y eficiente, simulando el comportamiento en una red real.

Según nosotros, logramos llevar a cabo la realización de cada uno de los requisitos, osea que podría decirse que no hubo ningún aspecto no logrado.

Lo que creemos que logramos comprender:

- Comprensión del Protocolo DHCP: A través de la implementación práctica, hemos profundizado en el funcionamiento del protocolo DHCP, desde el envío de solicitudes DHCPDISCOVER por parte del cliente hasta la asignación de direcciones IP por el servidor mediante el paquete DHCPACK. Este proceso nos permitió entender cómo se automatiza la configuración de red y cómo los dispositivos en una red pueden obtener sus configuraciones sin intervención manual.

- Uso de Sockets y Comunicación UDP: Implementar la comunicación cliente-servidor utilizando sockets Berkeley con SOCK_DGRAM nos permitió familiarizarnos con los detalles del protocolo UDP. A diferencia de otros protocolos orientados a la conexión, el uso de UDP demostró ser efectivo para la transmisión de mensajes rápidos y sin estado, alineándose perfectamente con las necesidades de DHCP, donde los mensajes son cortos y no requieren una conexión establecida.

- Entorno de Virtualización: Utilizar VirtualBox para simular el entorno de red entre dos máquinas virtuales fue una experiencia valiosa, ya que permitió crear y controlar un escenario similar al de una red física real sin requerir hardware adicional. La virtualización no solo simplificó las pruebas y la depuración, sino que también facilitó la experimentación con diferentes configuraciones de red.

- Optimización y Resolución de Problemas: Durante el desarrollo, aprendimos a manejar problemas comunes como la configuración de red en la máquina virtual, la sincronización entre el cliente y el servidor, y la correcta transmisión de paquetes broadcast. Estos desafíos mejoraron nuestra habilidad para depurar código y optimizar el rendimiento en un entorno distribuido

En conclusión, este proyecto no solo nos brindó la oportunidad de aplicar conceptos de redes y sistemas distribuidos, sino que también reforzó nuestra capacidad para implementar protocolos de comunicación de manera eficiente en un entorno virtual. La experiencia adquirida nos prepara mejor para abordar proyectos futuros relacionados con la administración y automatización de redes.

REFERENCIAS:

https://www.scaler.com/topics/udp-server-client-implementation-in-c/

Integrantes

- Samuel Lenis
- Jose Miguel Burgos
- Jeronimo Velasquez
