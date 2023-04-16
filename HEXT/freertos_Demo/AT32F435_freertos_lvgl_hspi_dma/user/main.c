/*
 * @Author: Letian-stu
 * @Date: 2023-04-14 21:12
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-04-16 14:42
 * @FilePath: \AT32F435_freertos_lvgl_hspi_dma\user\main.c
 * @Description: 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "main.h"
#include "ui.h"

TaskHandle_t App_main_Handler;
TaskHandle_t Lvgl_task_Handler;

void App_main(void *pvParameters)
{
  while (1)
  {
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton1, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton6, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton2, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton5, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton3, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
    lv_event_send(ui_ImgButton4, LV_EVENT_CLICKED, NULL);
    vTaskDelay(2000);
  }
}

void Lvgl_task(void *pvParameters)
{
  ui_init();
  while (1)
  {
    lv_task_handler();
    vTaskDelay(10);
  }
}

int main(void)
{
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA1_Channel1_IRQn, 0x01, 0);
  nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0x01, 0);

  system_clock_config();
  delay_init();
  uart_print_init(115200);

  LCD_Init();
  lv_init();
  lv_ms_tick_tim();
  lv_port_disp_init();
  taskENTER_CRITICAL();

  xTaskCreate((TaskFunction_t)App_main,
              (const char *)"App_main",
              (uint16_t)1024,
              (void *)NULL,
              (UBaseType_t)2,
              (TaskHandle_t *)&App_main_Handler);

  xTaskCreate((TaskFunction_t)Lvgl_task,
              (const char *)"lvgl_task",
              (uint16_t)1024,
              (void *)NULL,
              (UBaseType_t)1,
              (TaskHandle_t *)&Lvgl_task_Handler);

  taskEXIT_CRITICAL();

  vTaskStartScheduler();
}
