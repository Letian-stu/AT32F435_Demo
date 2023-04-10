/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
#include "stdio.h"
#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "drv_qspi.h"
/* Definitions of physical drive number for each drive */
//#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
//#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

#define QSPI_FLASH 0
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	switch (pdrv) {
	case QSPI_FLASH :
			
//			if(qspi_flash_read_id() != W25Q32_DRVID)					
//				stat = STA_NOINIT ;  	//��ⲻ��W25Q32
//		  else
//			{
//				//printf("fatfs status flash;id:0x%x\r\n",qspi_flash_read_id());
//				stat =  0;            //��ʼ���ɹ�
//			}
		stat = 0;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case QSPI_FLASH :
		qspi_flash_init();
		printf("fatfs init flash;id:0x%x\r\n",qspi_flash_read_id());
		return 0;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DSTATUS res;

	switch (pdrv) {
	case QSPI_FLASH :
	//printf("R: sector:%x count:%d\r\n",sector*4096,count*4096);	
	qspi_flash_data_read( sector*4096, buff,  count*4096);
	//�ú���û�з���ֵ������Ĭ�Ϸ�������;ÿ�������Ĵ�С��4096�����Դ����ײ����ʼ��ַ����sector*4096
	//Ҫ��ȡ���ٸ��ֽڣ����Ƕ�ȡ����������count*4096
		res = RES_OK;
		return res;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DSTATUS res;

	switch (pdrv) {
	case QSPI_FLASH :
		//printf("W: sector:%x count:%d\r\n",sector*4096,count*4096);
		//buff��const BYTE���ͣ���������һ����Ҫ����u8���ͣ����Դ˴�����ǿ��ת��
		qspi_flash_erase(sector*4096);
		qspi_flash_data_write(sector*4096, (u8*)buff, count*4096);
		res = RES_OK;
		return res;
	}
	return STA_NOINIT;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DSTATUS res;
	switch (pdrv) 
	{
		case QSPI_FLASH :
			switch(cmd)
			{
				//������������
				case GET_SECTOR_COUNT:
						*(DWORD *)buff = 1024; 
				break;
				//����������С
				case GET_SECTOR_SIZE:
						*(WORD *)buff = 4096 ;
				break;
				//���ز�����������С����
				case GET_BLOCK_SIZE:
						*(WORD *)buff = 1 ;   
				break;
			}
		res = RES_OK;         
		return res;
	}
	return STA_NOINIT;
}

