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

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

//#include "msdk_nvram_camera_exp.h"
//#include "msdk_lens_exp.h"
#include "camera_custom_nvram.h"
#include "camera_custom_lens.h"

const NVRAM_LENS_PARA_STRUCT FM50AF_LENS_PARA_DEFAULT_VALUE =
{
    //Version
    NVRAM_CAMERA_LENS_FILE_VERSION,

    // Focus Range NVRAM
    {0, 1023},

    // AF NVRAM
    {
        // -------- AF ------------
        {120, // i4Offset
          17, // i4NormalNum
          17, // i4MacroNum
           0, // i4InfIdxOffset
           0, //i4MacroIdxOffset          
    	{
             0, 40, 80,  86,  92, 98, 104, 110, 116, 122, 162,
           202, 242,   282, 362,   442,   532,   0,   0,   0,   0,
             0,   0,   0,      0,   0,   0,   0,   0,   0
            },
          15, // i4THRES_MAIN;
          10, // i4THRES_SUB;            
          4,  // i4INIT_WAIT;
          {500, 500, 500, 500, 500}, // i4FRAME_WAIT
          0,  // i4DONE_WAIT;
              
          147,  // i4FAIL_POS;

          33,  // i4FRAME_TIME                        
          5,  // i4FIRST_FV_WAIT;
            
          45,  // i4FV_CHANGE_THRES;
          10000,  // i4FV_CHANGE_OFFSET;        
          6,  // i4FV_CHANGE_CNT;
          0,  // i4GS_CHANGE_THRES;    
          20,  // i4GS_CHANGE_OFFSET;    
          6,  // i4GS_CHANGE_CNT;            
          12,  // i4FV_STABLE_THRES;         // percentage -> 0 more stable  
          10000,  // i4FV_STABLE_OFFSET;        // value -> 0 more stable
          6,  // i4FV_STABLE_NUM;           // max = 9 (more stable), reset = 0
          6,  // i4FV_STABLE_CNT;           // max = 9                                      
          12,  // i4FV_1ST_STABLE_THRES;        
          10000,  // i4FV_1ST_STABLE_OFFSET;
          6,  // i4FV_1ST_STABLE_NUM;                        
          6  // i4FV_1ST_STABLE_CNT;      
         },
         
         // -------- ZSD AF ------------
        {120, // i4Offset
          17, // i4NormalNum
          17, // i4MacroNum
           0, // i4InfIdxOffset
          0, //i4MacroIdxOffset                                               
   	{                                                                         
            0,  40, 80,  86,  92, 98, 104, 110, 116, 122, 162,                    
          202, 242,   282,   362,   442,   532,   0,   0,   0,   0,           
            0,   0,   0,   0,   0,   0,     0,   0,   0                    
           },                                                                 
           15, // i4THRES_MAIN;
           10, // i4THRES_SUB;            
           3,  // i4INIT_WAIT;
           {500, 500, 500, 500, 500}, // i4FRAME_WAIT
           0,  // i4DONE_WAIT;
                     
           147,  // i4FAIL_POS;

           66,  // i4FRAME_TIME                                  
           5,  // i4FIRST_FV_WAIT;
                     
           45,  // i4FV_CHANGE_THRES;
           10000,  // i4FV_CHANGE_OFFSET;        
           6,  // i4FV_CHANGE_CNT;
           40,  // i4GS_CHANGE_THRES;    
           10000,  // i4GS_CHANGE_OFFSET;    
           6,  // i4GS_CHANGE_CNT;            
           15,  // i4FV_STABLE_THRES;         // percentage -> 0 more stable  
           10000,  // i4FV_STABLE_OFFSET;        // value -> 0 more stable
           4,  // i4FV_STABLE_NUM;           // max = 9 (more stable), reset = 0
           4,  // i4FV_STABLE_CNT;           // max = 9                                      
           12,  // i4FV_1ST_STABLE_THRES;        
           10000,  // i4FV_1ST_STABLE_OFFSET;
           6,  // i4FV_1ST_STABLE_NUM;                        
           6  // i4FV_1ST_STABLE_CNT;      
           }, 
           
           // -------- VAFC ------------
        {120, // i4Offset
          17, // i4NormalNum
          17, // i4MacroNum
           0, // i4InfIdxOffset
           0, //i4MacroIdxOffset          
   	{                                                                   
            0,  40, 80,  86,  92, 98, 104, 110, 116, 122, 162,          
          202, 242,   282,   362,   442,   532,   0,   0,   0,   0,     
            0,   0,   0,   0,   0,   0,     0,   0,   0                 
           },                                                           
           15, // i4THRES_MAIN;
           10, // i4THRES_SUB;            
           1,  // i4INIT_WAIT;
           {500, 500, 500, 500, 500}, // i4FRAME_WAIT
           0,  // i4DONE_WAIT;
             
           147,  // i4FAIL_POS;

           33,  // i4FRAME_TIME                          
           5,  // i4FIRST_FV_WAIT;
             
           45,  // i4FV_CHANGE_THRES;
           10000,  // i4FV_CHANGE_OFFSET;        
           6,  // i4FV_CHANGE_CNT;
           40,  // i4GS_CHANGE_THRES;    
           10000,  // i4GS_CHANGE_OFFSET;    
           6,  // i4GS_CHANGE_CNT;            
           12,  // i4FV_STABLE_THRES;         // percentage -> 0 more stable  
           10000,  // i4FV_STABLE_OFFSET;        // value -> 0 more stable
           6,  // i4FV_STABLE_NUM;           // max = 9 (more stable), reset = 0
           6,  // i4FV_STABLE_CNT;           // max = 9                                      
           12,  // i4FV_1ST_STABLE_THRES;        
           10000,  // i4FV_1ST_STABLE_OFFSET;
           6,  // i4FV_1ST_STABLE_NUM;                        
           6  // i4FV_1ST_STABLE_CNT;      
          },

        // --- sAF_TH ---
         {
          8,   // i4ISONum;
          {100,150,200,300,400,600,800,1600},       // i4ISO[ISO_MAX_NUM];
                  
          6,   // i4GMeanNum;
          {20,55,105,150,180,205},        // i4GMean[GMEAN_MAX_NUM];

          { 89, 89, 89, 89, 89, 89, 89, 89,
            127, 127, 127, 127, 127, 127, 127, 127,
           180,180,180,180,180,180,180,180},        // i4GMR[3][ISO_MAX_NUM];
          
// ------------------------------------------------------------------------                  
          {142,1196,1036,1116,717,558,1116,6235,
           283,142, 283, 425,425,0,142,3587,
           0,   0,   0,   0,  0 ,0,0,478,
           177,425,  744, 531,248,390,354,2657,
           80,  0  , 0, 239, 80,0,159,3542,
           0,   0  ,0 , 80, 80,0,80,2878},        // i4FV_DC[GMEAN_MAX_NUM][ISO_MAX_NUM];
           
          {50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000},         // i4MIN_TH[GMEAN_MAX_NUM][ISO_MAX_NUM];        

          {   4,3,3,3,3,3,3,8,
              4,4,4,4,4,4,4,9,
              2,2,2,2,2,2,3,3,
              2,2,2,2,2,2,2,5,
              3,3,3,3,3,3,3,5,
              3,3,3,3,3,3,3,5}, // i4HW_TH[GMEAN_MAX_NUM][ISO_MAX_NUM];       
// ------------------------------------------------------------------------
          {0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0},        // i4FV_DC2[GMEAN_MAX_NUM][ISO_MAX_NUM];
           
          {0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0},         // i4MIN_TH2[GMEAN_MAX_NUM][ISO_MAX_NUM];
          
          {   5,5,6,5,5,5,7,13,
              5,6,6,6,6,7,7,9,
              5,6,4,5,4,5,5,9,
              4,4,4,4,4,4,5,6,
              4,4,4,5,5,5,5,7,
              5,5,6,5,5,5,4,10}      // i4HW_TH2[GMEAN_MAX_NUM][ISO_MAX_NUM];       
          
         },
// ------------------------------------------------------------------------

         // --- sZSDAF_TH ---
             {
          8,   // i4ISONum;
          {100,150,200,300,400,600,800,1600},       // i4ISO[ISO_MAX_NUM];
                  
          6,   // i4GMeanNum;
          {20,55,105,150,180,205},        // i4GMean[GMEAN_MAX_NUM];

          { 89, 89, 89, 89, 89, 89, 89, 89,
            127, 127, 127, 127, 127, 127, 127, 127,
           180,180,180,180,180,180,180,180},        // i4GMR[3][ISO_MAX_NUM];
          
// ------------------------------------------------------------------------                  
          {142,1196,1036,1116,717,558,1116,6235,
           283,142, 283, 425,425,0,142,3587,
           0,   0,   0,   0,  0 ,0,0,478,
           177,425,  744, 531,248,390,354,2657,
           80,  0  , 0, 239, 80,0,159,3542,
           0,   0  ,0 , 80, 80,0,80,2878},        // i4FV_DC[GMEAN_MAX_NUM][ISO_MAX_NUM];
           
          {50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000,
           50000,50000,50000,50000,50000,50000,50000,50000},         // i4MIN_TH[GMEAN_MAX_NUM][ISO_MAX_NUM];        

          {   4,3,3,3,3,3,3,8,
              4,4,4,4,4,4,4,9,
              2,2,2,2,2,2,3,3,
              2,2,2,2,2,2,2,5,
              3,3,3,3,3,3,3,5,
              3,3,3,3,3,3,3,5}, // i4HW_TH[GMEAN_MAX_NUM][ISO_MAX_NUM];       
// ------------------------------------------------------------------------
          {0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0},        // i4FV_DC2[GMEAN_MAX_NUM][ISO_MAX_NUM];
           
          {0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0},         // i4MIN_TH2[GMEAN_MAX_NUM][ISO_MAX_NUM];
          
          {   5,5,6,5,5,5,7,13,
              5,6,6,6,6,7,7,9,
              5,6,4,5,4,5,5,9,
              4,4,4,4,4,4,5,6,
              4,4,4,5,5,5,5,7,
              5,5,6,5,5,5,4,10}      // i4HW_TH2[GMEAN_MAX_NUM][ISO_MAX_NUM];       
          
         },

          1, // i4VAFC_FAIL_CNT;
          0, // i4CHANGE_CNT_DELTA;

          30, // i4LV_THRES;

          18, // i4WIN_PERCENT_W;
          24, // i4WIN_PERCENT_H;                
          116,  // i4InfPos;
          20, //i4AFC_STEP_SIZE;

          {
              {50, 100, 150, 200, 250}, // back to bestpos step
              { 0,   0,   0,   0,   0}  // hysteresis compensate step
          },

          {0, 50, 100, 200, 300}, // back jump
          400,  //i4BackJumpPos

          80, // i4FDWinPercent;
          100, // i4FDSizeDiff;

          3,   //i4StatGain          

          {0,0,0,0,0,0,0,0,0,0,
           0,0,0,0,0,0,0,0,0,0}// i4Coef[20];
    },

    {0}
};


UINT32 FM50AF_getDefaultData(VOID *pDataBuf, UINT32 size)
{
    UINT32 dataSize = sizeof(NVRAM_LENS_PARA_STRUCT);

    if ((pDataBuf == NULL) || (size < dataSize))
    {
        return 1;
    }

    // copy from Buff to global struct
    memcpy(pDataBuf, &FM50AF_LENS_PARA_DEFAULT_VALUE, dataSize);

    return 0;
}

PFUNC_GETLENSDEFAULT pFM50AF_getDefaultData = FM50AF_getDefaultData;


