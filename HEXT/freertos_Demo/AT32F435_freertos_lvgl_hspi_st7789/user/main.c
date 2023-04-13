#include "stdio.h"
#include "string.h"
#include "at32f435_437.h"
#include "at32f435_437_clock.h"
#include "at32f435_437_board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h"
#include "stream_buffer.h"
#include "message_buffer.h"
#include "semphr.h"
#include "lvgl.h"
#include "lv_tick_custom.h"
#include "bsp_spi_lcd.h"
#include "lv_port_disp_template.h"

TaskHandle_t App_main_Handler;

void App_main(void *pvParameters)
{	
	LCD_Init();
  lv_init();
	tmr4_int_init(191,999);
  lv_port_disp_init();
	lv_demo_benchmark();	
	while(1)
  {
    lv_task_handler(); 
		vTaskDelay(10);		
  }	
}

int main(void)
{
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  system_clock_config();
	delay_init();
  uart_print_init(115200);
	
  /* 进入临界区 */
  taskENTER_CRITICAL(); 

  xTaskCreate((TaskFunction_t )App_main,     
              (const char*    )"App_main",   
              (uint16_t       )512, 
              (void*          )NULL,
              (UBaseType_t    )5,
              (TaskHandle_t*  )&App_main_Handler); 		

							
  /* 退出临界区 */            
  taskEXIT_CRITICAL();  
							
  /* 开启任务调度器 */              
  vTaskStartScheduler();
}

