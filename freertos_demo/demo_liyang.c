#include "demo_liyang.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "demo_liyang_lwip.h"

uint8 demo_counter_hi;
TaskCfg_demo_t task_demo_hi_cfg = {1, 1000};
TaskHandle_t taskAHandle_demo_hi;
TaskCfg_demo_t msg_queue_hi;

static StackType_t  demoTaskStack[configDemo_STACK_SIZE];
static StaticTask_t demoTaskTCB;
UBaseType_t HighWater_hi;

uint8 demo_counter_mid;
TaskCfg_demo_t task_demo_mid_cfg = {1, 1};
TaskHandle_t taskAHandle_demo_mid;

uint8 demo_counter_lo;
TaskCfg_demo_t task_demo_lo_cfg = {1, 1};
TaskHandle_t taskAHandle_demo_lo;
TaskCfg_demo_t msg_queue_lo;

TaskHandle_t taskAHandle_demo_pcapif;


void demo_init()
{
    demo_lwip_init();

    // xTaskCreate( demo_task_mid, "DemoMid", configDemo_STACK_SIZE, &task_demo_mid_cfg, demoCHECK_TASK_PRIORITY_mid, &taskAHandle_demo_mid );
    xTaskCreate( demo_task_lo, "DemoLo", configDemo_STACK_SIZE, &task_demo_lo_cfg, demoCHECK_TASK_PRIORITY_lo, &taskAHandle_demo_lo );

    taskAHandle_demo_hi = xTaskCreateStatic(
        demo_task_hi,              // 任务函数
        "DemoHi",                  // 任务名
        configDemo_STACK_SIZE,     // 栈大小（words）
        &task_demo_hi_cfg,                      // 传入参数
        demoCHECK_TASK_PRIORITY_high,                         // 任务优先级
        demoTaskStack,             // 静态栈数组
        &demoTaskTCB               // 静态 TCB
    );

}

void demo_task_hi(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_hi = 0;

    for( ; ; )
    {   
        demo_task_udp_transmit();
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }

}

void demo_task_mid(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_mid = 0;

    demo_task_udp_receive();
    for( ; ; )
    {
        demo_counter_mid = demo_counter_mid + cfg->id;
        printf("demo mid counter is %d\n",demo_counter_mid);
        HighWater_hi = uxTaskGetStackHighWaterMark(taskAHandle_demo_hi );
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }
}

void demo_task_lo(void *arg)
{
    TaskCfg_demo_t *cfg = (TaskCfg_demo_t *)arg;
    TickType_t last = xTaskGetTickCount();
    demo_counter_lo = 0;
    printf("LowTask started\n");
    demo_task_tcp_receive();

    for( ; ; )
    {
        pcapif_poll_task();
        demo_counter_lo = demo_counter_lo + cfg->id;
        printf("demo lo counter is %d\n",demo_counter_lo);
        vTaskDelayUntil(&last, pdMS_TO_TICKS(cfg->period_ms));
    }
}