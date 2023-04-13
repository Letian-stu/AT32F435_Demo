#ifndef __LV_TICK_CUSTOM_H
#define __LV_TICK_CUSTOM_H


#include "at32f435_437.h"

void tmr4_int_init(u16 arr, u16 psc);
uint32_t millis(void);

#endif
