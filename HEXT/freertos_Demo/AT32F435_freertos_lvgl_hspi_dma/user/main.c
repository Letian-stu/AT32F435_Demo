#include "main.h"

TaskHandle_t App_main_Handler;

void App_main(void *pvParameters)
{	
	//lv_demo_benchmark();
	ui_init();
	ui_Screen1_screen_init();
	while(1)
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
	
  /* 进入临界区 */
  taskENTER_CRITICAL(); 

  xTaskCreate((TaskFunction_t )App_main,     
              (const char*    )"App_main",   
              (uint16_t       )512, 
              (void*          )NULL,
              (UBaseType_t    )1,
              (TaskHandle_t*  )&App_main_Handler); 			
							
  /* 退出临界区 */            
  taskEXIT_CRITICAL();  
							
  /* 开启任务调度器 */              
  vTaskStartScheduler();
}

