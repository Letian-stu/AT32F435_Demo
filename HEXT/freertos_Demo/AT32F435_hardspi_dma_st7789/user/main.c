#include "main.h"



#define BufferSize	240*240
uint16_t Buffer_Tx[BufferSize];


int main(void)
{
	system_clock_config();
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(DMA1_Channel1_IRQn, 1, 0);
	
	delay_init();
  uart_print_init(115200);
	
	LCD_Init();

	while(1)
	{		
		printf("doing\r\n");
		for(int i = 0; i < BufferSize; i++)
		{
			Buffer_Tx[i] = RED;
		}
		LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		delay_ms(1000);
		
		printf("doing\r\n");
		for(int i = 0; i < BufferSize; i++)
		{
			Buffer_Tx[i] = LIGHTBLUE;
		}
		LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		delay_ms(1000);

		printf("doing\r\n");
		for(int i = 0; i < BufferSize; i++)
		{
			Buffer_Tx[i] = LBBLUE;
		}
		LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		delay_ms(1000);

		printf("doing\r\n");
		for(int i = 0; i < BufferSize; i++)
		{
			Buffer_Tx[i] = WHITE;
		}
		LCD_DMA_Fill(0,0,240,240,Buffer_Tx);
		delay_ms(1000);		
	}
}

