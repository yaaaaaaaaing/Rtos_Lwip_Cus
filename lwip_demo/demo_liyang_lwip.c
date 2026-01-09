
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "lwip/ip_addr.h"
#include "lwip/ip4_addr.h"
#include "lwip/pbuf.h"

#pragma comment(lib, "ws2_32.lib")


static SOCKET udp_sock = INVALID_SOCKET;
static SOCKET tcp_sock = INVALID_SOCKET;
static struct sockaddr_in target_addr;
static struct sockaddr_in local_addr;

static struct udp_pcb *pcb;

void demo_lwip_init(void)
{

    /* the following code is used to send udp pack by windows socket API */ 
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    tcp_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 目标 IP/端口（你局域网的测试对端）
    target_addr.sin_family = AF_INET;
    target_addr.sin_port   = htons(5005);
    target_addr.sin_addr.s_addr = inet_addr("10.110.225.25");

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(49672);   // 发送端口固定
    local_addr.sin_addr.s_addr = INADDR_ANY;  // 本机所有网卡

    bind(udp_sock, (struct sockaddr*)&local_addr, sizeof(local_addr));
    bind(tcp_sock, (struct sockaddr*)&local_addr, sizeof(local_addr));

    printf("[INIT] UDP socket ready, target 10.0.0.200:5001\n");

    if (connect(tcp_sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) == SOCKET_ERROR) {
        printf("Failed to connect\n");
        return 1;
    }

    printf("[TCP CLIENT] Connected to server\n");

}

void demo_task_udp_transmit(void)
{

     /* the following code is used to send udp pack by windows socket API */    
    static unsigned int count = 0;

    char msg_udp[64];
    char msg_tcp[64];
    snprintf(msg_udp, sizeof(msg_udp), "UDP DEMO PACKET #%u", count++);
    snprintf(msg_tcp, sizeof(msg_udp), "TCP DEMO PACKET #%u", count++);

    // int r = sendto(udp_sock, msg_udp, (int)strlen(msg_udp), 0,
    //                (struct sockaddr*)&target_addr, sizeof(target_addr));

    send(tcp_sock, msg_tcp, (int)strlen(msg_tcp), 0);
    printf("[SENT] %s\n", msg_tcp);

    // printf("[UDP SEND] %s | result=%d\n", msg_udp, r);
}

void demo_task_udp_receive(void)
{
    char buf[1024];
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    while (1) {
        int r = recvfrom(udp_sock, buf, sizeof(buf)-1, 0,
                         (struct sockaddr*)&src_addr, &addrlen);
        if (r > 0) {
            buf[r] = '\0';
            printf("[RECEIVED] %s\n", buf);
        }
    }
}

void demo_task_tcp_receive(void)
{
    char buf[1024];
    struct sockaddr_in src_addr;
    int addrlen = sizeof(src_addr);
    while (1) {
        int r = recvfrom(tcp_sock, buf, sizeof(buf)-1, 0,
                         (struct sockaddr*)&src_addr, &addrlen);
        if (r > 0) {
            buf[r] = '\0';
            printf("[RECEIVED from server] %s\n", buf);
        }
    }
}

void pcapif_poll_task(void)
{
    // struct netif *netif = &g_netif;

    // pcapif_poll(netif);      // 喂包给 lwIP

}

#include <stdarg.h>

void lwip_win32_platform_diag(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg); // 输出到控制台
    va_end(arg);
}

#include <stdlib.h>
#include <time.h>

// 实现 LwIP 期待的随机数生成函数
unsigned int lwip_port_rand(void) {
    static int first_call = 1;
    if (first_call) {
        srand((unsigned int)time(NULL)); // 初始化随机种子
        first_call = 0;
    }
    return (unsigned int)rand();
}