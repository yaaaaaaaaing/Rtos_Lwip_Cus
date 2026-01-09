#ifndef LWIPOPTS_H
#define LWIPOPTS_H

// 最小协议栈功能使能
#define NO_SYS                  0
#define LWIP_SOCKET             1
#define LWIP_NETCONN            1
#define LWIP_UDP                1
#define LWIP_TCP                1
#define LWIP_ICMP               1
#define LWIP_DHCP               0
#define LWIP_ETHERNET           1

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
#define PCAPIF_RX_USE_THREAD            0u

// 让临界区保护完全走 FreeRTOS 的实现
#define LWIP_TCPIP_CORE_LOCKING    1
#define LWIP_COMPAT_MUTEX          1
#define LWIP_COMPAT_MUTEX_ALLOWED  1
#define SYS_LIGHTWEIGHT_PROT            1

/* 告诉 LwIP 不要自己定义字节序转换函数，因为 Windows 已经有了 */
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS 1

#define TCPIP_MBOX_SIZE             32    // tcpip_thread 接收消息的队列大小
#define DEFAULT_RAW_MBOX_SIZE       10    // Raw API 邮箱大小
#define DEFAULT_UDP_MBOX_SIZE       10    // UDP 邮箱大小
#define DEFAULT_TCP_MBOX_SIZE       10    // TCP 邮箱大小
#define DEFAULT_ACCEPTMBOX_SIZE     10    // 服务器 accept 队列大小

/* 基础 API 邮箱大小 */
#define DEFAULT_RAW_RECVMBOX_SIZE       10
#define DEFAULT_UDP_RECVMBOX_SIZE       10
#define DEFAULT_TCP_RECVMBOX_SIZE       10

/* 核心 TCP/IP 任务邮箱大小（非常重要！） */
#define TCPIP_MBOX_SIZE                 32

/* 核心 TCP/IP STACK SIZE */
#define TCPIP_THREAD_STACKSIZE          350

#endif // LWIPOPTS_H