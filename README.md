# ProyectoDHCP
¨Proyecto DHCP, Samuel Lenis, Jose Miguel Burgos, Jeronimo Velasquez

Introducción

Este proyecto tiene como objetivo implementar un servidor DHCP (Dynamic Host Configuration Protocol) utilizando dos máquinas virtuales conectadas a través de VirtualBox. La comunicación entre el servidor DHCP y el cliente se realizará mediante la API de sockets Berkeley, usando el formato de socket SOCK_DGRAM para la transmisión de datos.

En este entorno, un servidor DHCP alojado en una máquina virtual será el responsable de asignar dinámicamente direcciones IP y otros parámetros de configuración de red a una segunda máquina virtual cliente. A través del protocolo UDP, los mensajes de solicitud y respuesta se enviarán en formato broadcast para asegurar que el cliente pueda recibir la configuración de red de manera automática y eficiente, simulando el comportamiento en una red real.
