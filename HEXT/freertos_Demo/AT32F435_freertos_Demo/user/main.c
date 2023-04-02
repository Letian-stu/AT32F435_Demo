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
	crm_clocks_freq_type Get_Clocks;
  system_clock_config();
	
  uart_print_init(115200);
	crm_clocks_freq_get(&Get_Clocks);
	
	printf("System Clock information\r\n");
	printf("SYSCLK_Frequency = %d\r\n", (uint32_t) Get_Clocks.sclk_freq);
	printf("HCLK_Frequency   = %d\r\n", (uint32_t) Get_Clocks.ahb_freq);
	printf("PCLK1_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb1_freq);
	printf("PCLK2_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb2_freq);
  /* �����ٽ��� */
  taskENTER_CRITICAL(); 

  xTaskCreate((TaskFunction_t )App_main,     
              (const char*    )"App_main",   
              (uint16_t       )256, 
              (void*          )NULL,
              (UBaseType_t    )1,
              (TaskHandle_t*  )&App_main_Handler); 						
  /* �˳��ٽ��� */            
  taskEXIT_CRITICAL();  
  /* ������������� */              
  vTaskStartScheduler();
}

