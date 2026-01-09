#ifndef DEMO_LIYANG_LWIP_H
#define DEMO_LIYANG_LWIP_H

extern struct netif g_netif;

void demo_lwip_init(void);
void demo_task_udp_transmit(void);
void demo_task_udp_receive(void);
void demo_task_tcp_receive(void);
void pcapif_poll_task(void);

#endif