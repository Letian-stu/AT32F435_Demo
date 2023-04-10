# at32 with rtthread studio 

## 1.rtthread settings 开启spi设备

![微信截图_20230402160010](D:\C_Github\AT32F435_Demo\HEXT\rtthread_Demo\img\qspi1.png)

开启qspi设备会自己启动开启spi设备，需要把drv_spi.c内的下面这句屏蔽了

```c
#ifndef RT_USING_QSPI

//drv_spi.c内的代码

#endif
```



## 2.修改board.c board.h 

```c
//board.h 内添加
#define BSP_USING_QSPI
#define BSP_USING_QSPI1
//drv_qspi.c
#include <rtdevice.h>
//board.c 内添加
//提前修改at32_msp_qspi_init内的gpio配置
at32_msp_qspi_init(QSPI1);

```

## 3.在main.c添加 注册qspi和w25q32

```c
static void qspi_flash_sfud_init(void)
{
    rt_err_t ret = at32_qspi_bus_attach_device("qspi1", "qspi10", RT_NULL, 4, RT_NULL, RT_NULL);
    if (ret != RT_EOK)
    {
        LOG_I("qspi attach device failed");
        return -RT_ERROR;
    }
    LOG_I("qspi attach device success");
    /*   W25Q32 注册为快设备*/
    if (RT_NULL == rt_sfud_flash_probe("W25Q32", "qspi10"))
    {
        LOG_I("flash sfud failed");
        return -RT_ERROR;
    }
    LOG_I("flash sfud success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(qspi_flash_sfud_init);
```

## 4.开启文件系统

![](D:\C_Github\AT32F435_Demo\HEXT\rtthread_Demo\img\qspi2.png)

## 5.最后mian.c
```c
#include <rtthread.h>
#include <rtdevice.h>
#include "rtdef.h"
#include "drv_qspi.h"
#include "dfs_fs.h"
#include "spi_flash_sfud.h"

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
        rt_qspi_send_then_recv(qspi_dev_w25q, &w25x_read_id, 1, id, 5);
        LOG_I("use rt_qspi_send_then_recv() read w25q ID is:%x%x\n", id[3], id[4]);
    }

    /*   W25Q256 注册为快设备*/
    if (RT_NULL == rt_sfud_flash_probe("W25Q32", "qspi10"))
    {
        LOG_I("flash sfud failed");
        return -RT_ERROR;
    }
    LOG_I("flash sfud success");

    return RT_EOK;
}
INIT_DEVICE_EXPORT(qspi_flash_sfud_init);

static void mnt_init(void)
{
    dfs_mkfs("elm", "W25Q32");                          //格式化设备
    if( dfs_mount("W25Q32", "/", "elm", 0, 0) == 0 )    //挂载文件
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

int main(void)
{
    while (1)
    {
        //LOG_I("Hello RT-Thread!");
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}

```







