/*
 * @Author: Letian-stu
 * @Date: 2023-04-01 17:07
 * @LastEditors: Letian-stu
 * @LastEditTime: 2023-04-05 21:11
 * @FilePath: \projectd:\C_Github\AT32F435_Demo\HEXT\freertos_Demo\AT32F435_freertos_Demo\user\main.c
 * @Description:
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "main.h"

TaskHandle_t App_main_Handler;

void App_main(void *pvParameters)
{
	crm_clocks_freq_type Get_Clocks;
	crm_clocks_freq_get(&Get_Clocks);
	printf("System Clock information\r\n");
	printf("SYSCLK_Frequency = %d\r\n", (uint32_t)Get_Clocks.sclk_freq);
	printf("HCLK_Frequency   = %d\r\n", (uint32_t)Get_Clocks.ahb_freq);
	printf("PCLK1_Frequency  = %d\r\n", (uint32_t)Get_Clocks.apb1_freq);
	printf("PCLK2_Frequency  = %d\r\n", (uint32_t)Get_Clocks.apb2_freq);
	u8 task_buff[128];
	while (1)
	{
		printf("====================Task===================\r\n");
		printf("  name       state     pri     stack    num\r\n");
		vTaskList((char *)task_buff);
		printf("%s", task_buff);
		printf("===========================================\r\n");
		vTaskDelay(5000);
	}
}

int main(void)
{
	system_clock_config();
	uart_print_init(115200);
	taskENTER_CRITICAL();
	xTaskCreate((TaskFunction_t)App_main,
				(const char *)"App_main",
				(uint16_t)256,
				(void *)NULL,
				(UBaseType_t)1,
				(TaskHandle_t *)&App_main_Handler);
	taskEXIT_CRITICAL();
	vTaskStartScheduler();
}
