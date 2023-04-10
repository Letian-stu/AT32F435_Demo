#include "main.h"

TaskHandle_t App_main_Handler;
TaskHandle_t Lvgl_tick_Handler;

void App_main(void *pvParameters)
{
	while(1)
	{
		printf("app main task doing\r\n");
		vTaskDelay(1000);
		gpio_bits_write(GPIOA, GPIO_PINS_3, FALSE);
		vTaskDelay(1000);
		gpio_bits_write(GPIOA, GPIO_PINS_3, TRUE);
	}
}

void Lvgl_tick(void *pvParameters)
{
	while(1)
	{
		lv_timer_handler();
		vTaskDelay(5);
	}
}

void gpio_config(void)
{
  gpio_init_type gpio_init_struct;

  /* enable the gpioa clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure the gpio */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_3;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);
}

int main(void)
{
	crm_clocks_freq_type Get_Clocks;
  system_clock_config();
	
  uart_print_init(115200);
	crm_clocks_freq_get(&Get_Clocks);
	
	gpio_config();
	
	printf("System Clock information\r\n");
	printf("SYSCLK_Frequency = %d\r\n", (uint32_t) Get_Clocks.sclk_freq);
	printf("HCLK_Frequency   = %d\r\n", (uint32_t) Get_Clocks.ahb_freq);
	printf("PCLK1_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb1_freq);
	printf("PCLK2_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb2_freq);
  /* 进入临界区 */
  taskENTER_CRITICAL(); 

//	lv_init();
//	lv_port_disp_init();
	
//#if LV_USE_DEMO_BENCHMARK
//  lv_demo_benchmark();
//#endif
	
  xTaskCreate((TaskFunction_t )App_main,     
              (const char*    )"App_main",   
              (uint16_t       )256, 
              (void*          )NULL,
              (UBaseType_t    )1,
              (TaskHandle_t*  )&App_main_Handler); 	
							
//  xTaskCreate((TaskFunction_t )Lvgl_tick,     
//              (const char*    )"Lvgl_tick",   
//              (uint16_t       )256, 
//              (void*          )NULL,
//              (UBaseType_t    )1,
//              (TaskHandle_t*  )&Lvgl_tick_Handler); 									
  /* 退出临界区 */            
  taskEXIT_CRITICAL();  
  /* 开启任务调度器 */              
  vTaskStartScheduler();
}

