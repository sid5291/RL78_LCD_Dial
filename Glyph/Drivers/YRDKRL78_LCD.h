/*-------------------------------------------------------------------------*
 * File:  YRDKRL78_RSPI0.h
 *-------------------------------------------------------------------------*
 * Description:
 *    Y Renesas Development Kit (RDK) for Renesas RL78 Group CPU
 * RSPI Transmitter 0 Operation channel 3.  Routines for RSPI code running
 * on RL78 CPU, RSPI0.  This program uses RSPI0.  The Chip Select for the
 * flash device (LCD) is set to PC_2.  This is the RSPI channel used to
 * communicate with the ST7579 Graphics Display.
 *
 * The RSPI configuration has the baud rate generator set
 * for maximum speed, which is PLCK/2 or 25 MHz.
 *
 * Manufacturer: Renesas
 * Communications Protocol: SPI 3-Wire Transmitt only MASTER SPI
 * Transmitter Number: 0
 * channel: 3
 * Chip Select Port: PC.2
 * SPI Clock Speed: 25MHz
 * Slave Device: OKAYA LCD with ST7579 microprocessor
 *
 *-------------------------------------------------------------------------*/
 
#ifndef __GLYPH__YRDK_RL78_SPI_0_HEADER_FILE
#define __GLYPH__YRDK_RL78_SPI_0_HEADER_FILE

/******************************************************************************
Includes �Glyph Include�
******************************************************************************/
#include "r_cg_userdefine.h"
#include "glyph_api.h"
 

#ifdef RDKRL78G13

#define SPI_LCD_RS_PORT P1
#define SPI_LCD_RS_BIT_POS (5)

#endif
	 
#ifdef RDKRL78G14

#define SPI_LCD_RS_PORT P14
#define SPI_LCD_RS_BIT_POS (6)

#endif
	 
	 
/******************************************************************************
Prototypes for the Glyph Communications API
******************************************************************************/
void YRDKRL78_CommandSend(int8_t cCommand) ;
void YRDKRL78_DataSend(int8_t cData) ;
void YRDKRL78_DataSend_1(char *,uint16_t) ;
T_glyphError YRDKRL78_RSPIOpen(T_glyphHandle aHandle);

#endif /* __GLYPH__YRDK_RL78_SPI_0_HEADER_FILE */
 
 
