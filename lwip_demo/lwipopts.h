#ifndef LWIPOPTS_H
#define LWIPOPTS_H

// 最小协议栈功能使能
#define NO_SYS                  0
#define LWIP_SOCKET             1
#define LWIP_NETCONN            1
#define LWIP_UDP                1
#define LWIP_TCP                0
#define LWIP_ICMP               1
#define LWIP_DHCP               0

// 内存配置（最小）
#define MEM_ALIGNMENT           4
#define MEM_SIZE                16000
#define MEMP_NUM_UDP_PCB        2
#define MEMP_NUM_PBUF           8
#define PBUF_POOL_SIZE          8
#define ETH_PAD_SIZE            2

// Debug 关闭（避免控制台噪音）
#define LWIP_DEBUG              0

#define MEMP_NUM_SYS_TIMEOUT            10u
#define PACKET_LIB_ADAPTER_NR           1u

#endif // LWIPOPTS_H