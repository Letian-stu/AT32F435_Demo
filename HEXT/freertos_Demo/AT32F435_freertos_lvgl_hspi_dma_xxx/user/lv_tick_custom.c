#include "lvgl.h"
#include "lv_tick_custom.h"

volatile static uint32_t system_ms = 0;

/**
  * @brief  get the systick by ms
  * @param  none
  * @retval ms
  */
uint32_t millis(void)
{
    return system_ms;
}

void lv_ms_tick_tim(void)
{
	crm_clocks_freq_type crm_clocks_freq_struct = {0};
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	
  /* enable tmr1 clock */
  crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

	//Tout(us) = ����arr+1��*��psc+1����/Tclk ; 
  tmr_base_init(TMR1, 99, (crm_clocks_freq_struct.apb2_freq * 2 / 100000) - 1);
	
  tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

  /* overflow interrupt enable */
  tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);

  /* enable tmr1 */
  tmr_counter_enable(TMR1, TRUE);	
}
 
void TMR1_OVF_TMR10_IRQHandler(void)
{
  if(tmr_flag_get(TMR1, TMR_OVF_FLAG) == SET)
  {
		system_ms++;  
		
		//lv_tick_inc(1);
    tmr_flag_clear(TMR1, TMR_OVF_FLAG);
  }
}

