#include "main.h"

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

