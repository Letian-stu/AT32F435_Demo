/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

#include "lv_port_disp_template.h"
#include <stdbool.h>
#include "bsp_spi_lcd.h"

#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif

static const char *TAG = "lv_port_disp";
static lv_color_t lvgl_draw_buff1[LVGL_BUFF_SIZE];
static lv_color_t lvgl_draw_buff2[LVGL_BUFF_SIZE];

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /* �ȴ��ϴδ������ */
    bsp_lcd_draw_rect_wait();
    /* ֪ͨlvgl��������� */
    lv_disp_flush_ready(disp_drv);
    /* �����µĴ��� */
    bsp_lcd_draw_rect(area->x1, area->y1, area->x2, area->y2, (const uint8_t*)color_p);
}
		
void lv_port_disp_init(void)
{
    /* ��lvglע�Ỻ���� */
    static lv_disp_draw_buf_t draw_buf_dsc; //��Ҫȫ���������ڣ�����Ϊ��̬����
    lv_disp_draw_buf_init(&draw_buf_dsc, lvgl_draw_buff1, lvgl_draw_buff2, sizeof(lvgl_draw_buff1)/sizeof(lv_color_t));

    /* ��������ʼ��������lvgl��ע����ʾ�豸�Ľṹ */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); //ʹ��Ĭ��ֵ��ʼ���ýṹ
    /* ������Ļ�ֱ��� */
    disp_drv.hor_res = BSP_LCD_X_PIXELS;
    disp_drv.ver_res = BSP_LCD_Y_PIXELS;
    /* ��ʼ��LCD���� */
    bsp_lcd_init();
    /* ������ʾ���κ��������ڽ����λ�����ˢ�µ���Ļ�� */
    disp_drv.flush_cb = disp_flush;
    /* ���û����� */
    disp_drv.draw_buf = &draw_buf_dsc;
    /* ע����ʾ�豸 */
    lv_disp_drv_register(&disp_drv);

    /* ������ʾ */
    bsp_lcd_display_switch(1);
}



#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
