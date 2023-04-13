/* define to prevent recursive inclusion -------------------------------------*/
#ifndef _DRV_USBD_H
#define _DRV_USBD_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "usb_conf.h"
#include "usb_core.h"
#include "usbd_int.h"
#include "msc_class.h"
#include "msc_desc.h"
#include "msc_diskio.h"
#include "FreeRTOS.h"
#include "task.h"



void usb_delay_ms(uint32_t ms);
void usb_clock48m_select(usb_clk48_s clk_s);
void usb_gpio_config(void);
void usb_low_power_wakeup_config(void);
void usb_drv_config(void);

#ifdef __cplusplus
}
#endif

#endif
