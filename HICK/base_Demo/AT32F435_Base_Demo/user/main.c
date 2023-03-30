#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"

__IO uint32_t time_cnt = 0;


int main(void)
{
  system_clock_config();
  at32_board_init();
  uart_print_init(115200);

  printf("usart printf example: retarget the c library printf function to the usart\r\n");
  while(1)
  {
    printf("usart printf counter: %u\r\n",time_cnt++);
    delay_sec(1);
  }
}

