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
	
//  /* initialize qspi flash */
//  qspi_flash_init();

//  /* erase sector 0 */
//  qspi_flash_erase(0);

//	printf("strlen:%d\r\n",strlen((char *)write_buf));
//  /* write data to quad spi flash */
//  qspi_flash_data_write(0xff, write_buf, strlen((char *)write_buf) );
//  printf("write: %s\r\n",write_buf);

//  /* read data from quad spi flash */
//  qspi_flash_data_read(0xff, read_buf, strlen((char *)write_buf) );
//	printf("read: %s\r\n",read_buf);
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

