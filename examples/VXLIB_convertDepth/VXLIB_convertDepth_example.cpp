// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_bufParams.h"
#include "VXLIB_types.h"
#include "vxlib.h"
#include <cstdio>
#include <stdint.h>

#define height (3)
#define width (3)

/******************************************************************************/
/*                                                                            */
/* main                                                                       */
/*                                                                            */
/******************************************************************************/

int main(void)
{

   // clang-format off
    
    int16_t in0_i16[] = {-32767, -7500, 500,
                         -5500, 150, 600,
                          400, 100, -10};
    
    uint8_t out_u8[] = {0, 0, 0,
		                0, 0, 0,
		                0, 0, 0};
    uint8_t shift = 3;

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS                status;
   VXLIB_convertDepth_InitArgs kerInitArgs;
   int32_t                     handleSize = VXLIB_convertDepth_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle          handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_INT16;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(int16_t);

   bufParamsOut.data_type = VXLIB_UINT8;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(uint8_t);

   kerInitArgs.funcStyle      = VXLIB_FUNCTION_OPTIMIZED;
   kerInitArgs.overFlowPolicy = VXLIB_WRAP;
   kerInitArgs.shift          = shift;

   status = VXLIB_SUCCESS;

   // init checkparams
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // exec checkparams
   if (status == VXLIB_SUCCESS)
      VXLIB_convertDepth_exec_checkParams(handle, in0_i16, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_exec(handle, in0_i16, out_u8);

   printf("16 BIT TO 8 BIT IMAGE - WRAP POLICY");
   // print results
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%d, ", out_u8[i * width + j]);
      }
   }
   printf("\n\n");

   kerInitArgs.overFlowPolicy = VXLIB_SATURATE;

   status = VXLIB_SUCCESS;

   // init checkparams
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // exec checkparams
   if (status == VXLIB_SUCCESS)
      VXLIB_convertDepth_exec_checkParams(handle, in0_i16, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_exec(handle, in0_i16, out_u8);

   printf("16 BIT TO 8 BIT IMAGE - SATURATE POLICY");
   // print results
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%d, ", out_u8[i * width + j]);
      }
   }
   printf("\n\n");

   // clang-format off
    
    uint8_t in0_u8[] = {67, 75, 50,
                        55, 150, 60,
                        40, 100, 10};
    
    int16_t out_i16[] = {0, 0, 0,
		                0, 0, 0,
		                0, 0, 0};

   // clang-format on

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   kerInitArgs.funcStyle      = VXLIB_FUNCTION_OPTIMIZED;
   kerInitArgs.overFlowPolicy = VXLIB_WRAP;
   kerInitArgs.shift          = shift;

   status = VXLIB_SUCCESS;

   // init checkparams
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // exec checkparams
   if (status == VXLIB_SUCCESS)
      VXLIB_convertDepth_exec_checkParams(handle, in0_u8, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_convertDepth_exec(handle, in0_u8, out_i16);

   printf("8 BIT TO 16 BIT IMAGE");
   // print results
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%d, ", out_i16[i * width + j]);
      }
   }
   printf("\n\n");

   free(handle);

   return 0;
}