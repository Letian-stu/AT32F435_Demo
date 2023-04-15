#include "stdio.h"
#include "string.h"
#include "at32f435_437.h"
#include "at32f435_437_clock.h"
#include "at32f435_437_board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "timers.h"
#include "stream_buffer.h"
#include "message_buffer.h"
#include "semphr.h"

#include "lvgl.h"
#include "lv_tick_custom.h"
#include "bsp_spi_lcd.h"
#include "lv_port_disp_template.h"


volatile uint32_t debug_timerTick;//任务运行时间统计使用  




