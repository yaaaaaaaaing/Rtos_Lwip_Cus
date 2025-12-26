
#include "lwip/netif.h"
#include "lwip/init.h"
#include "pcapif.h"
#include "netif/ethernet.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"

struct netif g_netif;

void demo_lwip_init(void)
{
    ip_addr_t ipaddr, netmask, gw;
    lwip_init();

    IP4_ADDR(&ipaddr, 10, 110, 224, 222);
    IP4_ADDR(&netmask, 255, 255, 240, 0);
    IP4_ADDR(&gw, 10, 110, 224, 1);
    netif_add(&g_netif, &ipaddr, &netmask, &gw, NULL, pcapif_init, ethernet_input);
    netif_set_default(&g_netif);
    netif_set_up(&g_netif);
    netif_set_link_up(&g_netif);
}

void demo_task_main(void)
{
    struct udp_pcb *pcb = udp_new();
    if (!pcb) {
        printf("udp_new failed!\n");
    }

    ip_addr_t dest_ip;
    IP4_ADDR(&dest_ip, 192, 168, 1, 100);
    const uint16_t dest_port = 5005;

    const char *msg = "hello ethernet via lwip";
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, strlen(msg), PBUF_RAM);
    memcpy(p->payload, msg, strlen(msg));

    err_t err = udp_sendto(pcb, p, &dest_ip, dest_port);
    if (err != ERR_OK) {
        printf("UDP send failed with error: %d\n", (int)err);
    } else {
        printf("UDP packet sent!\n");
    }

    pbuf_free(p);
    udp_remove(pcb);
}

void pcapif_poll_task(void *arg)
{
    struct netif *netif = (struct netif *)arg;

    for (;;)
    {
        pcapif_poll(netif);      // 喂包给 lwIP
        vTaskDelay(pdMS_TO_TICKS(10));  // FreeRTOS 延时 10ms
    }
}