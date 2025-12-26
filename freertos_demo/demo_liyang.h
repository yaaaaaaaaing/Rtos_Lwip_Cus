#ifndef DEMO_LIYANG_FREERTOS_H
#define DEMO_LIYANG_FREERTOS_H
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

#define configDemo_STACK_SIZE 1024u
#define demoCHECK_TASK_PRIORITY_high    ( configMAX_PRIORITIES - 1 )
#define demoCHECK_TASK_PRIORITY_mid     ( configMAX_PRIORITIES - 2 )
#define demoCHECK_TASK_PRIORITY_lo      ( configMAX_PRIORITIES - 3 )

typedef unsigned char uint8;
typedef unsigned short uint16;

typedef struct
{
    uint8 id;
    uint16 period_ms;
} TaskCfg_demo_t;

void demo_task_hi(void *arg);
void demo_task_mid(void *arg);
void demo_task_lo(void *arg);

extern void demo_init();

extern SemaphoreHandle_t xSharedResource;
extern TaskCfg_demo_t task_demo_hi_cfg;
extern TaskHandle_t taskAHandle_demo_hi;
extern TaskCfg_demo_t task_demo_mid_cfg;
extern TaskHandle_t taskAHandle_demo_mid;
extern TaskCfg_demo_t task_demo_lo_cfg;
extern TaskHandle_t taskAHandle_demo_lo;

#endif