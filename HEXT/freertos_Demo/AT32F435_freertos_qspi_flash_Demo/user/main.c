#include "main.h"

uint8_t write_buf[1024] = "hello world";
uint8_t read_buf[1024];

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

