/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_userdefine.h
* Version      : Applilet3 for RL78/G14 V2.00.00.08 [12 Apr 2013]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file includes user definition.
* Creation Date: 4/16/2014
***********************************************************************************************************************/

#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/

/* Start user code for function. Do not edit comment generated here */

#define RDKRL78G14 // or RDKRL78G13 for old board

#define MAX(a,b) ((a>b)? a : b)
#define MIN(a,b) ((a<b)? a : b)

#define LED_3_R P6_bit.no2
#define LED_5_R P6_bit.no3
#define LED_7_R P6_bit.no4
#define LED_4_G P4_bit.no2
#define LED_6_G P4_bit.no3
#define LED_8_G P4_bit.no4

#define LED_15_O P4_bit.no1

#define DIR_OUT	0
#define DIR_IN  1

#define LED_3_R_M PM6_bit.no2
#define LED_5_R_M PM6_bit.no3
#define LED_7_R_M PM6_bit.no4
#define LED_4_G_M PM4_bit.no2
#define LED_6_G_M PM4_bit.no3
#define LED_8_G_M PM4_bit.no4
#define LED_15_O_M PM4_bit.no1


#define SW_1 P7_bit.no6
#define SW_2 P7_bit.no5
#define SW_3 P7_bit.no4

typedef struct { uint8_t X, Y;} PointT;

/* End user code. Do not edit comment generated here */
#endif
