#ifndef DEMO_LIYANG_LWIP_H
#define DEMO_LIYANG_LWIP_H

extern struct netif g_netif;

void demo_lwip_init(void);
void demo_task_main(void);
void pcapif_poll_task(void *arg);

#endif