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

TaskHandle_t App_main_Handler;

void App_main(void *pvParameters)
{
	while(1)
	{
		printf("app main task doing\r\n");
		vTaskDelay(1000);
	}
}

int main(void)
{
  system_clock_config();
  uart_print_init(115200);
  /* 进入临界区 */
  taskENTER_CRITICAL(); 

  xTaskCreate((TaskFunction_t )App_main,     
              (const char*    )"App_main",   
              (uint16_t       )256, 
              (void*          )NULL,
              (UBaseType_t    )1,
              (TaskHandle_t*  )&App_main_Handler); 						
  /* 退出临界区 */            
  taskEXIT_CRITICAL();  
  /* 开启任务调度器 */              
  vTaskStartScheduler();
}

