/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif
// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH  (720)
#define FRAME_HEIGHT (1280)

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#define REGFLAG_DELAY                                       0XFFE
#define REGFLAG_END_OF_TABLE                                0xFFF   // END OF REGISTERS MARKER


#define LCM_ID    0x1283

// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)    (lcm_util.set_reset_pin((v)))




#define UDELAY(n) (lcm_util.udelay(n))
#define MDELAY(n) (lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	        lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)										lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)					lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)											lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)   				lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)   


//#define   LCM_DSI_CMD_MODE							0

static struct LCM_setting_table
{
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

#if 0
static struct LCM_setting_table lcm_initialization_setting[] =
{
	{0xff,3,{0x12,0x83,0x01 							  }},
	{0x00,1,{0x80										  }},
	{0xff,2,{0x12,0x83									  }},
	{0x00,1,{0x90										  }},
	{0xf5,4,{0x02,0x11,0x02,0x11						  }},
	{0x00,1,{0x90										  }},
	{0xc5,1,{0x50										  }},
	{0x00,1,{0x94										  }},
	{0xc5,1,{0x77										  }},
	{0x00,1,{0x80										  }},
	{0xc0,9,{0x00,0x64,0x00,0x10,0x10,0x00,0x64,0x10,0x10 }},
	{0x00,1,{0x90}},
	{0xc0,6,{0x00,0x5c,0x00,0x01,0x00,0x04}},
	{0x00,1,{0xb3						 }},
	{0xc0,2,{0x00,0x50					 }},
	{0x00,1,{0x81						 }},
	{0xc1,1,{0x55						 }},
    {0x00,1,{0xa0}},
    {0xc1,1,{0x02}},  		
	{0x00,1,{0xa0						 }},
	{0xc4,14,{0x05,0x10,0x06,0x02,0x05,0x15,0x10,0x05,0x10,0x07,0x02,0x05,0x15,0x10}},
	{0x00,1,{0xb0	 }},
	{0xc4,2,{0x00,0x00}},
	{0x00,1,{0x91	  }},
	{0xc5,2,{0x46,0x40}},
	{0x00,1,{0x00	  }},
	{0xd8,2,{0xbc,0xbc}},
	{0x00,1,{0x00	  }},
	{0xd9,1,{0x30	  }},
	{0x00,1,{0xb0	  }},
	{0xc5,2,{0x04,0x38}},
	{0x00,1,{0xbb	  }},
	{0xc5,1,{0x80	  }},
	{0x00,1,{0xc3	  }},
	{0xf5,1,{0x81	  }},
	{0x00,1,{0x82	  }},
	{0xf4,1,{0x00	  }},
	{0x00,1,{0x80	  }},
	{0xc6,1,{0x24	  }},
	{0x00,1,{0x00	  }},
	{0xd0,1,{0x40	  }},
	{0x00,1,{0x00	  }},
	{0xd1,2,{0x00,0x00}},
	{0x00,1,{0x80	  }},
	{0xcb,11,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0x90}},
	{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xa0}},
	{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xb0}},
	{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xc0}},
	{0xcb,15,{0x05,0x00,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xd0}},
	{0xcb,15,{0x00,0x00,0x00,0x05,0x00,0x05,0x05,0x05,0x00,0x05,0x05,0x05,0x05,0x00,0x00}},
	{0x00,1,{0xe0}},
	{0xcb,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x05,0x05}},
	{0x00,1,{0xf0}},
	{0xcb,11,{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}},
	{0x00,1,{0x80}},
	{0xcc,15,{0x02,0x00,0x0a,0x0e,0x0c,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0x90}},
	{0xcc,15,{0x00,0x00,0x00,0x06,0x00,0x2e,0x2d,0x01,0x00,0x09,0x0d,0x0b,0x0f,0x00,0x00}},
	{0x00,1,{0xa0}},
	{0xcc,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x2e,0x2d}},
	{0x00,1,{0xb0}},
	{0xcc,15,{0x05,0x00,0x0f,0x0b,0x0d,0x09,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xc0}},
	{0xcc,15,{0x00,0x00,0x00,0x01,0x00,0x2d,0x2e,0x06,0x00,0x10,0x0c,0x0e,0x0a,0x00,0x00}},
	{0x00,1,{0xd0}},
	{0xcc,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x2d,0x2e}},
	{0x00,1,{0x80}},
	{0xce,12,{0x87,0x03,0x18,0x86,0x03,0x18,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0x90}},
	{0xce,14,{0x34,0xfe,0x18,0x34,0xff,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xa0}},
	{0xce,14,{0x38,0x03,0x05,0x00,0x00,0x18,0x00,0x38,0x02,0x05,0x01,0x00,0x18,0x00}},
	{0x00,1,{0xb0}},
	{0xce,14,{0x38,0x01,0x05,0x02,0x00,0x18,0x00,0x38,0x00,0x05,0x03,0x00,0x18,0x00}},
	{0x00,1,{0xc0}},
	{0xce,14,{0x30,0x00,0x05,0x04,0x00,0x18,0x00,0x30,0x01,0x05,0x05,0x00,0x18,0x00}},
	{0x00,1,{0xd0}},
	{0xce,14,{0x30,0x02,0x05,0x06,0x00,0x18,0x00,0x30,0x03,0x05,0x07,0x00,0x18,0x00}},
	{0x00,1,{0x80}},
	{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0x90}},
	{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xa0}},
	{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xb0}},
	{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x00,1,{0xc0}},
	{0xcf,10,{0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x01,0x00,0x00}},
	{0x00,1,{0xb5}},
	{0xc5,6,{0x37,0xf1,0xfd,0x37,0xf1,0xfd}},
	{0x00,1,{0x90}},
	{0xc4,1,{0x49}},
	{0x00,1,{0x82}},
	{0xC4,1,{0x02}},
	{0x00,1,{0xc6}},
	{0xb0,1,{0x03}},
	{0x00,1,{0x94}},
	{0xF5,1,{0x02}},
	{0x00,1,{0xBA}},
	{0xF5,1,{0x03}},
	{0x00,1,{0x00}},
	{0xE1,16,{0x00,0x08,0x0D,0x0D,0x06,0x11,0x0D,0x0C,0x01,0x05,0x08,0x07,0x0D,0x12,0x0F,0x0D}},
	{0x00,1,{0x00}},
	{0xE2,16,{0x00,0x08,0x0D,0x0D,0x06,0x11,0x0D,0x0C,0x01,0x05,0x08,0x07,0x0D,0x12,0x0F,0x0D}},
	{0x00,1,{0x90}},
	{0xb3,1,{0x02}},
	{0x00,1,{0x92}},
	{0xb3,1,{0x40}},
	{0x00,1,{0x80}},
	{0xf6,1,{0x01}},
	{	0X11,0X00,{}},	
	{REGFLAG_DELAY, 120, {}},
	{	0X29,0X00,{}},		
	{REGFLAG_DELAY, 100, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}		
};

#else   //S539 �׿���
static struct LCM_setting_table lcm_initialization_setting[] =
{
	    {0x00,1,{0x00}},
		{0xff,3,{0x12,0x83,0x01}},	//EXTC=1
	
		{0x00,1,{0x80}},			//Orise mode enable
		{0xff,2,{0x12,0x83}},
	
	//-------------------- panel setting --------------------//
		{0x00,1,{0x80}},			 //TCON Setting
		{0xc0,9,{0x00,0x64,0x00,0x10,0x10,0x00,0x64,0x10,0x10}},
	
		{0x00,1,{0x90}},			 //Panel Timing Setting
		{0xc0,6,{0x00,0x5c,0x00,0x01,0x00,0x04}},
	
		{0x00,1,{0xa4}},			 //source pre. 
		{0xc0,1,{0x22}},
	
		{0x00,1,{0xb3}},			 //Interval Scan Frame: 0 frame, column inversion
		{0xc0,2,{0x00,0x50}},
	
		{0x00,1,{0x81}},			 //frame rate:60Hz
		{0xc1,1,{0x55}},
	
		{0x00,1,{0x90}},			 //clock delay for data latch 
		{0xc4,1,{0x49}},
	
	//-------------------- power setting --------------------//
		{0x00,1,{0xa0}},			 //dcdc setting
		{0xc4,14,{0x05,0x10,0x06,0x02,0x05,0x15,0x10,0x05,0x10,0x07,0x02,0x05,0x15,0x10}},
	
		{0x00,1,{0xb0}},			 //clamp voltage setting
		{0xc4,2,{0x00,0x00}},
	
		{0x00,1,{0x91}},			 //VGH=15V, VGL=-10V, pump ratio:VGH=6x, VGL=-5x
		{0xc5,2,{0x46,0x40}},
	
		{0x00,1,{0x00}},			 //GVDD=5.008V, NGVDD=-5.008V
		{0xd8,2,{0xc7,0xc7}},
	
		{0x00,1,{0x00}},			 //VCOMDC=-1.584
		{0xd9,1,{0x7D}},
	
		{0x00,1,{0x81}},			 //source bias 0.75uA
		{0xc4,1,{0x82}},
	
		{0x00,1,{0xb0}},			 //VDD_18V=1.6V, LVDSVDD=1.55V
		{0xc5,2,{0x04,0xb8}},
	
		{0x00,1,{0xbb}},			 //LVD voltage level setting
		{0xc5,1,{0x80}},
	
		{0x00,1,{0x82}},		// chopper 0: frame 2: line 4: disable
		{0xC4,1,{0x02}}, 
	
		{0x00,1,{0xc6}},		// debounce
		{0xB0,1,{0x03}}, 
	
	//-------------------- control setting --------------------//
		{0x00,1,{0x00}},			 //ID1
		{0xd0,1,{0x40}},
	
		{0x00,1,{0x00}},			 //ID2, ID3
		{0xd1,2,{0x00,0x00}},
	
	//-------------------- panel timing state control --------------------//
		{0x00,1,{0x80}}, 
		{0xcb,11,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0x90}}, 
		{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xa0}}, 
		{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xb0}},  
		{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xc0}}, 
		{0xcb,15,{0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00,0x00,0x00,0x05,0x05,0x00,0x05,0x05}},
	
		{0x00,1,{0xd0}}, 
		{0xcb,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x00}},
	
		{0x00,1,{0xe0}},
		{0xcb,14,{0x00,0x00,0x05,0x05,0x00,0x05,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xf0}},
		{0xcb,11,{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}},
	
	//-------------------- panel pad mapping control --------------------//
		{0x00,1,{0x80}}, 
		{0xcc,15,{0x0E,0x10,0x0A,0x0C,0x02,0x04,0x00,0x00,0x00,0x00,0x2E,0x2D,0x00,0x29,0x2A}},
	
		{0x00,1,{0x90}},	
		{0xcc,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0D,0x0F,0x09,0x0B,0x01,0x03,0x00,0x00}},
	
		{0x00,1,{0xa0}}, 
		{0xcc,14,{0x00,0x00,0x2E,0x2D,0x00,0x29,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xb0}}, 
		{0xcc,15,{0x0B,0x09,0x0F,0x0D,0x03,0x01,0x00,0x00,0x00,0x00,0x2D,0x2E,0x00,0x29,0x2A}},
	
		{0x00,1,{0xc0}}, 
		{0xcc,15,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0A,0x10,0x0E,0x04,0x02,0x00,0x00}},
	
		{0x00,1,{0xd0}},  
		{0xcc,14,{0x00,0x00,0x2D,0x2E,0x00,0x29,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
	//-------------------- panel timing setting --------------------//
		{0x00,1,{0x80}},			 //panel VST setting
		{0xce,12,{0x8B,0x03,0x18,0x8A,0x03,0x18,0x89,0x03,0x18,0x88,0x03,0x18}},
	
		{0x00,1,{0x90}},			 //panel VEND setting
		{0xce,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xa0}},			 //panel CLKA1/2 setting
		{0xce,14,{0x38,0x07,0x05,0x00,0x00,0x18,0x00,0x38,0x06,0x05,0x01,0x00,0x18,0x00}},
	
		{0x00,1,{0xb0}},			 //panel CLKA3/4 setting
		{0xce,14,{0x38,0x05,0x05,0x02,0x00,0x18,0x00,0x38,0x04,0x05,0x03,0x00,0x18,0x00}},
	
		{0x00,1,{0xc0}},			 //panel CLKb1/2 setting
		{0xce,14,{0x38,0x03,0x05,0x04,0x00,0x18,0x00,0x38,0x02,0x05,0x05,0x00,0x18,0x00}},
	
		{0x00,1,{0xd0}},			 //panel CLKb3/4 setting
		{0xce,14,{0x38,0x01,0x05,0x06,0x00,0x18,0x00,0x38,0x00,0x05,0x07,0x00,0x18,0x00}},
	
		{0x00,1,{0x80}},			 //panel CLKc1/2 setting
		{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0x90}},			 //panel CLKc3/4 setting
		{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xa0}},			 //panel CLKd1/2 setting
		{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xb0}},			 //panel CLKd3/4 setting
		{0xcf,14,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	
		{0x00,1,{0xc0}},			 //panel ECLK setting
		{0xcf,11,{0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x81,0x00,0x03,0x08}}, //gate pre. ena.
	
		{0x00,1,{0xb5}},			 //TCON_GOA_OUT Setting
		{0xc5,6,{0x00,0x6f,0xfF,0x00,0x6f,0xfF}},
	
	//-------------------- for Power IC --------------------//
		{0x00,1,{0x90}},			 //Mode-3
		{0xf5,4,{0x02,0x11,0x02,0x11}},
	
		{0x00,1,{0x90}},			 //2xVPNL
		{0xc5,1,{0x50}},
	
		{0x00,1,{0x94}},			 //Freq.
		{0xc5,1,{0x66}},
	
	//------------------VGLO1/O2 disable----------------
		{0x00,1,{0xb2}},			 //VGLO1
		{0xf5,2,{0x00,0x00}},
	
		{0x00,1,{0xb4}},			 //VGLO1_S
		{0xf5,2,{0x00,0x00}},
	
		{0x00,1,{0xb6}},			 //VGLO2
		{0xf5,2,{0x00,0x00}},
	
		{0x00,1,{0xb8}},			 //VGLO2_S
		{0xf5,2,{0x00,0x00}},
	
		{0x00,1,{0x94}},		//VCL on	
		{0xF5,1,{0x02}},
	
		{0x00,1,{0xBA}},		//VSP on	
		{0xF5,1,{0x03}},
	
		{0x00,1,{0xb4}},			 //VGLO1/2 Pull low setting
		{0xc5,1,{0xc0}},		//d[7] vglo1 d[6] vglo2 => 0: pull vss, 1: pull vgl
	
	//-------------------- Gamma --------------------//
		{0x00,1,{0x00}},
		{0xE1,16,{0x00,0x08,0x0e,0x0d,0x06,0x0e,0x0a,0x0a,0x04,0x07,0x0f,0x08,0x0f,0x13,0x0d,0x06}},
	
		{0x00,1,{0x00}},
		{0xE2,16,{0x00,0x08,0x0e,0x0d,0x06,0x0e,0x0a,0x0a,0x04,0x07,0x0f,0x08,0x0f,0x13,0x0d,0x06}},
	
	
		{0x00,1,{0x00}},			 //Orise mode disable
		{0xff,3,{0xff,0xff,0xff}},
	
		{0x11, 1,{0x00}},
		{REGFLAG_DELAY, 120, {}},
	
		{0x29, 1,{0x00}},
		{REGFLAG_DELAY, 30, {}},	   

	    {REGFLAG_END_OF_TABLE, 0x00, {}}
};
#endif

static struct LCM_setting_table lcm_sleep_in_setting[] =
{
    // Display off sequence
    {0x28, 0, {0x00}},

    // Sleep Mode On
    {0x10, 0, {0x00}},

    {REGFLAG_END_OF_TABLE, 0x00, {}}
};

static struct LCM_setting_table lcm_sleep_out_setting[] =
{
    // Sleep Out
    {0x11, 0, {0x00}},
    {REGFLAG_DELAY, 120, {}},

    // Display ON
    {0x29, 0, {0x00}},
    {REGFLAG_DELAY, 10, {}},

    {REGFLAG_END_OF_TABLE, 0x00, {}}
};


static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
    unsigned int i;

    for(i = 0; i < count; i++)
    {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd)
        {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
//                dsi_set_cmdq_dcs(cmd, table[i].count, table[i].para_list, force_update);
        }
    }

}

static void init_lcm_registers(void)
{
	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}



// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

		memset(params, 0, sizeof(LCM_PARAMS));
	
		params->type   = LCM_TYPE_DSI;

		params->width  = FRAME_WIDTH;
		params->height = FRAME_HEIGHT;

		// enable tearing-free
		params->dbi.te_mode 				= LCM_DBI_TE_MODE_VSYNC_ONLY;
		params->dbi.te_edge_polarity		= LCM_POLARITY_RISING;

        #if (LCM_DSI_CMD_MODE)
		params->dsi.mode   = CMD_MODE;
        #else
		params->dsi.mode   = BURST_VDO_MODE;
		//params->dsi.mode   = SYNC_EVENT_VDO_MODE; 
		
        #endif
	
		// DSI
		/* Command mode setting */
		//1 Three lane or Four lane
//		params->dsi.LANE_NUM				= LCM_THREE_LANE;
		params->dsi.LANE_NUM				= LCM_FOUR_LANE;
		//The following defined the fomat for data coming from LCD engine.
		params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
		params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
		params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
		params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

		// Highly depends on LCD driver capability.
		// Not support in MT6573
		params->dsi.packet_size=256;

		// Video mode setting		
		params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

		params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
		params->dsi.word_count=720*3;	
		params->dsi.compatibility_for_nvk = 0;
		
		params->dsi.vertical_sync_active				= 2;
		params->dsi.vertical_backporch					= 14;
		params->dsi.vertical_frontporch					= 16;
		params->dsi.vertical_active_line				= FRAME_HEIGHT; 

		params->dsi.horizontal_sync_active				= 2;
		params->dsi.horizontal_backporch				= 34;
		params->dsi.horizontal_frontporch				= 24;
		params->dsi.horizontal_active_pixel				= FRAME_WIDTH;  // ?��?�� ((150+150+10)+720)*((20+20+4)+1280)*60*24=
																			// 1030 x 1324 x60 x 24 / 4

        //	params->dsi.HS_PRPR=6;
	    //params->dsi.LPX=8; 
		//params->dsi.HS_PRPR=5;
		//params->dsi.HS_TRAIL=13;
	//	params->dsi.CLK_TRAIL = 10;
		// Bit rate calculation
		//1 Every lane speed
		params->dsi.pll_div1=0;		// div1=0,1,2,3;div1_real=1,2,4,4 ----0: 546Mbps  1:273Mbps
		params->dsi.pll_div2=1;		// div2=0,1,2,3;div1_real=1,2,4,4	
		params->dsi.fbk_div =15;    //fref=26MHz, fvco=fref*(fbk_div+1)*2/(div1_real*div2_real)

#ifdef LENOVO_BACKLIGHT_LIMIT
 		params->bl_app.min =1;
  		params->bl_app.def =102;
  		params->bl_app.max =255;
  		params->bl_bsp.min =7;
  		params->bl_bsp.def =102;
  		params->bl_bsp.max =255;
#endif
}

static void lcm_init(void)
{

	mt_set_gpio_mode(GPIO131, GPIO_MODE_07);
	mt_set_gpio_dir(GPIO131, GPIO_DIR_OUT);
    	mt_set_gpio_out(GPIO131, 1);
	MDELAY(5);
    	mt_set_gpio_out(GPIO131, 0);
	MDELAY(5);	
   	 mt_set_gpio_out(GPIO131, 1);
	MDELAY(10);		
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	
	SET_RESET_PIN(1);
	MDELAY(10);      

	init_lcm_registers();

}


static void lcm_suspend(void)
{
	unsigned int data_array[16];

	mt_set_gpio_out(GPIO155, 0);//diable backlight ic

//	push_table(lcm_sleep_in_setting, sizeof(lcm_sleep_in_setting) / sizeof(struct LCM_setting_table), 1);
    SET_RESET_PIN(1);
	MDELAY(20);
    SET_RESET_PIN(0);
    MDELAY(20);
	data_array[0]=0x00280500; // Display Off
	dsi_set_cmdq(data_array, 1, 1);
	
	data_array[0] = 0x00100500; // Sleep In
	dsi_set_cmdq(data_array, 1, 1);

	SET_RESET_PIN(0);
}


static void lcm_resume(void)
{
	int i;
/*
	unsigned int data_array[16];
	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(50);

	SET_RESET_PIN(1);
	MDELAY(50);
	init_lcm_registers();
	MDELAY(100); 	 */
	lcm_init();

	mt_set_gpio_out(GPIO155, 1);//enable backlight ic

}
         
#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);
	
	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(&data_array, 3, 1);

	data_array[0]= 0x00290508; //HW bug, so need send one HS packet
	dsi_set_cmdq(&data_array, 1, 1);
	
	data_array[0]= 0x002c3909;
	dsi_set_cmdq(&data_array, 1, 0);

}
#endif

static void lcm_setbacklight(unsigned int level)
{
	unsigned int data_array[16];


	if(level > 255) 
	level = 255;

	data_array[0] = 0x00023902;      
	data_array[1] = (0x51|(level<<8)); 
	dsi_set_cmdq(&data_array, 2, 1); 

}

static unsigned int lcm_compare_id(void)
{
	unsigned char lcd_id = 0;
	unsigned int id=0;
	unsigned char buffer[5];
	unsigned int array[16];  

	SET_RESET_PIN(1);
	MDELAY(10); 	
	SET_RESET_PIN(0);
	MDELAY(20);
	
	SET_RESET_PIN(1);
	MDELAY(80);  

// {0xff,3,{0x12,0x83,0x01 							  }},
	array[0]=0x00043902;
	array[1]=0x018312ff;// page enable
	
	dsi_set_cmdq(&array, 2, 1);
	MDELAY(10);
	
	array[0] = 0x00053700;// return byte number
	dsi_set_cmdq(&array, 1, 1);
	MDELAY(10);

	read_reg_v2(0xA1, buffer, 5);
//	id = buffer[2]; //we only need ID
	
#ifdef BUILD_LK
	printf("lcm_compare_id otm1283a buffer[0] = 0x%x,buffer[1] = 0x%x,buffer[2] = 0x%x,buffer[3] = 0x%x,buffer[4] = 0x%x\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
#else
	printk("lcm_compare_id otm1283a buffer[0] = 0x%x,buffer[1] = 0x%x,buffer[2] = 0x%x,buffer[3] = 0x%x,buffer[4] = 0x%x\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);

#endif


	if((buffer[0]==0x01)&&(buffer[1]==0x8b)&&(buffer[2]==0x12)&&(buffer[3]==0x83))
	{
		return 1;
	}
	else
	{
		return 0;
	}	


}
static unsigned int lcm_esd_check(void)
{
#ifndef BUILD_LK
//#if 1
	char  buffer[3];
	int   array[4];

	array[0] = 0x00013700;
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0x0a, buffer, 1);
	printk("jacob test lcm_esd_check buffer[0]=0x%x\n",buffer[0]);
	if(buffer[0]==0x9c)
	{
		return FALSE;
	}
	else
	{	
		return TRUE;
	}
#else
	return FALSE;
#endif
}



static unsigned int lcm_esd_recover(void)
{
#ifndef BUILD_LK	
	lcm_init();
//	MDELAY(100);
//	lcm_init();
	printk("jacob test lcm_esd_recover\n");
#endif
	return TRUE;
}


LCM_DRIVER otm1283a_hd720_dsi_vdo_lcm_drv = 
{
    .name			= "otm1283a_hd720_dsi_vdo",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	.compare_id     = lcm_compare_id,
	.esd_check   = lcm_esd_check,
    .esd_recover   = lcm_esd_recover,	
#if (LCM_DSI_CMD_MODE)
	.set_backlight	= lcm_setbacklight,
    .update         = lcm_update,
#endif
    };
