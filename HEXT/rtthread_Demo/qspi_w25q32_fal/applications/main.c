/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "rtdef.h"
#include "drv_qspi.h"
#include "dfs_fs.h"
#include "spi_flash_sfud.h"
#include "fal.h"

#include "usb_core.h"
#include "usbd_int.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

static void qspi_flash_sfud_init(void)
{
    struct rt_spi_device *qspi_dev_w25q;
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};

    rt_err_t ret = at32_qspi_bus_attach_device("qspi1", "qspi10", RT_NULL, 4, RT_NULL, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_I("qspi attach device failed");
        return -RT_ERROR;
    }
    LOG_I("qspi attach device success");

    qspi_dev_w25q = (struct rt_spi_device *)rt_device_find("qspi10");
    if (!qspi_dev_w25q)
    {
        LOG_I("spi sample run failed! can't find device!");
    }
    else
    {
        /* 方式1：使用 rt_spi_send_then_recv()发送命令读取ID */
        rt_qspi_send_then_recv(qspi_dev_w25q, &w25x_read_id, 1, id, 5);
        LOG_I("use rt_spi_send_then_recv() read w25q ID is:%x%x", id[3], id[4]);

        /* 方式2：使用 rt_spi_transfer_message()发送命令读取ID */
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_read_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = id;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        rt_qspi_transfer_message(qspi_dev_w25q, &msg1);
        LOG_I("use rt_spi_transfer_message() read w25q ID is:%x%x", id[3], id[4]);
    }

    /*   W25Q256 注册为快设备*/
    if (RT_NULL == rt_sfud_flash_probe("W25Q32", "qspi10"))
    {
        LOG_I("flash sfud failed");
        return -RT_ERROR;
    }
    LOG_I("flash sfud success");

    fal_init();
    LOG_I("fal success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(qspi_flash_sfud_init);

static void mnt_init(void)
{
    fal_blk_device_create("easyflash");                    // 注意调用该函数前必须要先调用fal_init函数初始化
    //dfs_mkfs("elm", "easyflash");                        //格式化设备
    if( dfs_mount("easyflash", "/", "elm", 0, 0) == 0 )    //挂载文件
    {
        LOG_I("dfs mount success");
        return RT_EOK;
    }
    else
    {
        LOG_I("dfs mount failed");
        return -RT_ERROR;
    }
}
INIT_COMPONENT_EXPORT(mnt_init);

static void readwrite_sample(void)
{
    int fd, size;
    char write_buff[] = "hello tian hello world";
    char buffer[80];

    fd = open("/updata.txt", O_RDWR | O_CREAT);
    if (fd >= 0)
    {
        write(fd, write_buff, sizeof(write_buff));
        close(fd);
        rt_kprintf("Write done size %d \n",sizeof(write_buff) );
    }

    fd = open("/updata.txt", O_RDWR);
    if (fd >= 0)
    {
        size = read(fd, buffer, sizeof(write_buff));
        close(fd);
        rt_kprintf("size:%d read: %s\n",size, buffer);
    }
}
MSH_CMD_EXPORT(readwrite_sample, readwrite sample);

#define USB_DEV_NAME   "hidd"
static rt_device_t usb_dev;
static void hid_send_sample(void)
{
    rt_err_t res;
    rt_uint8_t usb_sendbuf[32];
    rt_memset(usb_sendbuf, 0x66, 32);
    usb_dev = rt_device_find(USB_DEV_NAME);
    if (!usb_dev) {
        rt_kprintf("find %s failed!\n", USB_DEV_NAME);
        return RT_ERROR;
    }
    else {
        rt_kprintf("find %s success!\n", USB_DEV_NAME);
    }
    res = rt_device_open(usb_dev, RT_DEVICE_OFLAG_RDWR);
    if (res != RT_EOK) {
        rt_kprintf("send to %s failed!\n", USB_DEV_NAME);
        return RT_ERROR;
    }
    else {
        rt_kprintf("send to %s success!\n", USB_DEV_NAME);
    }
    rt_device_write(usb_dev, HID_REPORT_ID_GENERAL, usb_sendbuf, 4);
}
MSH_CMD_EXPORT(hid_send_sample, hid_send_sample);

int main(void)
{
    while (1)
    {
      rt_thread_mdelay(5000);
    }
    return RT_EOK;
}
