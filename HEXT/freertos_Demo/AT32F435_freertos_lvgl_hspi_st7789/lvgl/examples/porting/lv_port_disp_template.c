#if 1

#include "lv_port_disp_template.h"
#include <stdbool.h>
#include "bsp_spi_lcd.h"

#define ONE_FLUSH_SIZES    40
#define MY_DISP_HOR_RES    240
#define MY_DISP_VER_RES    240

#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif


static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);


void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t draw_buf_dsc_2;                      
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * ONE_FLUSH_SIZES];                       
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * ONE_FLUSH_SIZES];                       
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * ONE_FLUSH_SIZES);  

    static lv_disp_drv_t disp_drv;                       
    lv_disp_drv_init(&disp_drv);                  

    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf_dsc_2;

    lv_disp_drv_register(&disp_drv);
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
	int32_t x;
	int32_t y;

	LCD_Address_Set(area->x1,area->y1,area->x2,area->y2); 
	for(y = area->y1; y <= area->y2; y++) {
			for(x = area->x1; x <= area->x2; x++) {
					/*Put a pixel to the display. For example:*/
					/*put_px(x, y, *color_p)*/
					LCD_WR_DATA(color_p->full);
					color_p++;
			}
	}
	lv_disp_flush_ready(disp_drv);
}


#endif
