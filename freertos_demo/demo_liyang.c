#include "demo_liyang.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "demo_liyang_lwip.h"

uint8 demo_counter_hi;
TaskCfg_demo_t task_demo_hi_cfg = {1, 100};
TaskHandle_t taskAHandle_demo_hi;
TaskCfg_demo_t msg_queue_hi;

uint8 demo_counter_mid;
TaskCfg_demo_t task_demo_mid_cfg = {1, 1};
TaskHandle_t taskAHandle_demo_mid;

uint8 demo_counter_lo;
TaskCfg_demo_t task_demo_lo_cfg = {1, 2};
TaskHandle_t taskAHandle_demo_lo;
TaskCfg_demo_t msg_queue_lo;


void demo_init()
{
    demo_lwip_init();
    xTaskCreate( demo_task_hi, "DemoHI", configDemo_STACK_SIZE, &task_demo_hi_cfg, demoCHECK_TASK_PRIORITY_high, &taskAHandle_demo_hi );

}

void demo_task_hi(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_hi = 0;

    for( ; ; )
    {   
        demo_task_main();
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }

}

void demo_task_mid(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_mid = 0;

    for( ; ; )
    {
        demo_counter_mid = demo_counter_mid + cfg->id;
        printf("demo mid counter is %d\n",demo_counter_mid);
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }
}

void demo_task_lo(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_lo = 0;

    printf("LowTask started\n");

    for( ; ; )
    {
        demo_counter_lo = demo_counter_lo + cfg->id;
        printf("demo lo counter is %d\n",demo_counter_lo);
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }
}