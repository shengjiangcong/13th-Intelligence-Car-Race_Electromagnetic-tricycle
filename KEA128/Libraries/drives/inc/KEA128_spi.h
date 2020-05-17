#ifndef _KEA128_spi_h
#define _KEA128_spi_h
#include "misc.h"
#include "common.h"
#include "SKEAZ1284.h"
#include "KEA128_port_cfg.h"
//主从机模式
typedef enum
{
    MASTER,    //主机模式
    SLAVE      //从机模式
} SPI_CFG;


//模块号
typedef enum
{
    spi0,
    spi1,
} SPIn_e;


//SPI模块片选号
typedef enum
{
    NOT_PCS,
    USE_PCS,
} SPI_PCSn_e;


uint32 spi_init(SPIn_e spin , SPI_PCSn_e pcs, SPI_CFG master,uint32 baud);
void spi_mosi(SPIn_e spin, SPI_PCSn_e pcs, uint8 *modata, uint8 *midata, uint32 len);
void spi_mosi_cmd(SPIn_e spin, SPI_PCSn_e pcs, uint8 *mocmd , uint8 *micmd , uint8 *modata , uint8 *midata, uint32 cmdlen , uint32 len);

#endif 
