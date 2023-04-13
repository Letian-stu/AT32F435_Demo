#include "main.h"
#include "drv_qspi.h"
#include "drv_usbd.h"
#include "ff.h"
#include "diskio.h"

TaskHandle_t App_main_Handler;

uint16_t a;

BYTE work[FF_MAX_SS]; //һ����һ��ȫ�ֱ���
FATFS fs;  //һ����һ��ȫ�ֱ���
FIL fp;    //�ļ�����
char *write_text="tian nbnb a one day day go !!!!";
UINT write_bytes=0;

char read_buff[512];
UINT read_bytes=0;

void App_main(void *pvParameters)
{
	crm_clocks_freq_type Get_Clocks;
	crm_clocks_freq_get(&Get_Clocks);
	printf("System Clock information\r\n");
	printf("SYSCLK_Frequency = %d\r\n", (uint32_t) Get_Clocks.sclk_freq);
	printf("HCLK_Frequency   = %d\r\n", (uint32_t) Get_Clocks.ahb_freq);
	printf("PCLK1_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb1_freq);
	printf("PCLK2_Frequency  = %d\r\n", (uint32_t) Get_Clocks.apb2_freq);
	
	FRESULT  res ;   //�ֲ�����
	res = f_mount(&fs,  "0:",  1);   //�����ļ�ϵͳ �� "1:"���ǹ��ص��豸��Ϊ1���豸

	if(res == FR_NO_FILESYSTEM)  //FR_NO_FILESYSTEMֵΪ13����ʾû����Ч���豸
	{
		printf("res = FR_NO_FILESYSTEM\r\n");
		res = f_mkfs("0:",0,work,sizeof(work));
		printf("res = %d\r\n",res);
		res = f_mount(NULL,  "0:",  1);  			 //ȡ���ļ�ϵͳ
		printf("res = %d\r\n",res);
		res = f_mount(&fs,  "0:",  1);   			 //�����ļ�ϵͳ
		printf("res = %d\r\n",res);
		if(res == 0)
		{
			printf("mount success\r\n");
		}
 	}
	else if(res == 0)
	{
		printf("mount success\r\n");
	}
	
//	if(!f_open(&fp,"0:tian.txt",FA_OPEN_ALWAYS | FA_WRITE | FA_READ))
//	{
//		printf("open file success!\r\n");
//		if(FR_OK == f_write(&fp,(char*)write_text,strlen(write_text),&write_bytes))
//		{
//			printf("write success,write_bytes=%d\r\n",write_bytes);
//		}
//		else 
//			printf("write failure!\r\n");
//		
//		if(!f_close(&fp))
//		{
//			printf("close success!\r\n");
//		}
//		else 
//			printf("close failure!\r\n");
//	}
//	else 
//		printf("open file failure!\r\n");
	
	
	
	res = f_open(&fp,"0:tian.txt",FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
	if(!res)
	{
		printf("open file success!\r\n");
		if(FR_OK == f_read(&fp,(char*)read_buff,strlen(write_text),&read_bytes))
		{
			printf("read = %s\r\n",read_buff);
			printf("read success,read_bytes=%d\r\n",read_bytes);
		}
		else 
			printf("read failure!\r\n");
		
		if(!f_close(&fp))
		{
			printf("close success!\r\n");
		}
		else 
			printf("close failure!\r\n");
	}
	else 
		printf("open file failure!%d\r\n",res);		
	while(1)
	{
		printf("app main task doing\r\n");
		vTaskDelay(8000);
	}
}

int main(void)
{
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  system_clock_config();
  uart_print_init(115200);
	printf("start init usbd\r\n");
	usb_drv_config();
	
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


