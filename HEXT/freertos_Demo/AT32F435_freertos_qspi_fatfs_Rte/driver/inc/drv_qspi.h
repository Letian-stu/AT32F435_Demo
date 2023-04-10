/* define to prevent recursive inclusion -------------------------------------*/
#ifndef _DRV_QSPI_H
#define _DRV_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"


#define W25Q32_DRVID 0xef15
#define QSPI_FLASH_FIFO_DEPTH            4096
#define QSPI_FLASH_PAGE_SIZE             256

#define QSPI_FLASH_QSPIx                 QSPI1
#define QSPI_FLASH_QSPI_CLK              CRM_QSPI1_PERIPH_CLOCK

#define QSPI_FLASH_CS_GPIO_CLK           CRM_GPIOB_PERIPH_CLOCK
#define QSPI_FLASH_CS_GPIO_PIN           GPIO_PINS_10
#define QSPI_FLASH_CS_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE10
#define QSPI_FLASH_CS_GPIO_PORT          GPIOB
#define QSPI_FLASH_CS_GPIO_MUX           GPIO_MUX_9

#define QSPI_FLASH_CLK_GPIO_CLK          CRM_GPIOB_PERIPH_CLOCK
#define QSPI_FLASH_CLK_GPIO_PIN          GPIO_PINS_1
#define QSPI_FLASH_CLK_GPIO_PINS_SOURCE  GPIO_PINS_SOURCE1
#define QSPI_FLASH_CLK_GPIO_PORT         GPIOB
#define QSPI_FLASH_CLK_GPIO_MUX          GPIO_MUX_9

#define QSPI_FLASH_D0_GPIO_CLK           CRM_GPIOA_PERIPH_CLOCK
#define QSPI_FLASH_D0_GPIO_PIN           GPIO_PINS_6
#define QSPI_FLASH_D0_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE6
#define QSPI_FLASH_D0_GPIO_PORT          GPIOA
#define QSPI_FLASH_D0_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D1_GPIO_CLK           CRM_GPIOA_PERIPH_CLOCK
#define QSPI_FLASH_D1_GPIO_PIN           GPIO_PINS_7
#define QSPI_FLASH_D1_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE7
#define QSPI_FLASH_D1_GPIO_PORT          GPIOA
#define QSPI_FLASH_D1_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D2_GPIO_CLK           CRM_GPIOC_PERIPH_CLOCK
#define QSPI_FLASH_D2_GPIO_PIN           GPIO_PINS_4
#define QSPI_FLASH_D2_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE4
#define QSPI_FLASH_D2_GPIO_PORT          GPIOC
#define QSPI_FLASH_D2_GPIO_MUX           GPIO_MUX_10

#define QSPI_FLASH_D3_GPIO_CLK           CRM_GPIOC_PERIPH_CLOCK
#define QSPI_FLASH_D3_GPIO_PIN           GPIO_PINS_5
#define QSPI_FLASH_D3_GPIO_PINS_SOURCE   GPIO_PINS_SOURCE5
#define QSPI_FLASH_D3_GPIO_PORT          GPIOC
#define QSPI_FLASH_D3_GPIO_MUX           GPIO_MUX_10

/**
  * @brief qspi flash exported functions
  */
void qspi_flash_init(void);
uint16_t qspi_flash_read_id(void);
void qspi_flash_data_read(uint32_t addr, uint8_t* buf, uint32_t total_len);
void qspi_flash_data_write(uint32_t addr, uint8_t* buf, uint32_t total_len);
void qspi_flash_erase(uint32_t sec_addr);

void qspi_flash_erase_block(uint32_t blo_addr);
void qspi_flash_erase_all(void);

#ifdef __cplusplus
}
#endif

#endif

