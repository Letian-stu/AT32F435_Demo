#include "freertos_tick.h"

volatile uint32_t debug_timerTick;//��������ʱ��ͳ��ʹ��  
extern   uint32_t systemcoreclock;

void TIMER_Init(void)
{
  /* ʹ��TMR2ʱ�� */
  crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);

  /* ��ʼ��TMR2 */
  tmr_base_init(TMR2, systemcoreclock/10000, 10);
  tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
  
  tmr_interrupt_enable(TMR2, TMR_OVF_INT, TRUE);
  
  nvic_irq_enable(TMR2_GLOBAL_IRQn, 2, 0);
  
  tmr_base_init(TMR3, 65535, 20000);
  tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);

  tmr_interrupt_enable(TMR3, TMR_OVF_INT, TRUE);
  
  nvic_irq_enable(TMR3_GLOBAL_IRQn, 2, 0);
  
  /* ʹ��TMR2 */
  tmr_counter_enable(TMR2, TRUE);
}

void TMR2_GLOBAL_IRQHandler(void)
{
  if(tmr_flag_get(TMR2, TMR_OVF_FLAG) != RESET)
  {
    debug_timerTick++;
    tmr_flag_clear(TMR2, TMR_OVF_FLAG);
  }
}












