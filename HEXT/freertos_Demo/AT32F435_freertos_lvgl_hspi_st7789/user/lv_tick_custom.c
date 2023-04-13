#include "lvgl.h"
#include "lv_tick_custom.h"

volatile static uint32_t system_ms = 0;

uint32_t millis(void)
{
    return system_ms;
}

void tmr4_int_init(u16 arr, u16 psc)
{
  /* enable tmr7 clock */
  crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);

  tmr_base_init(TMR4, arr, psc);
  tmr_cnt_dir_set(TMR4, TMR_COUNT_UP);
  tmr_interrupt_enable(TMR4, TMR_OVF_INT, TRUE);

  /* tmr1 overflow interrupt nvic init */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(TMR4_GLOBAL_IRQn, 0, 4);

  /* enable tmr7 */
  tmr_counter_enable(TMR4, TRUE);  
}
 
void TMR4_GLOBAL_IRQHandler(void)
{ 		  
  TMR4->ists = 0;
  system_ms++;  
}

