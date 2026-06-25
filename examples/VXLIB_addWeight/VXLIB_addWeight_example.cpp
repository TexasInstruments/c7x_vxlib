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
    
   uint8_t in0_u8[] = {10, 20, 30,
                       40, 50, 60,
                       70, 80, 90};

   uint8_t in1_u8[] = {110, 120, 130,
                       140, 150, 160,
                       170, 180, 190};

   float alpha = 0.3;
  
   uint8_t out_u8[] = {0, 0, 0,
		       0, 0, 0,
	               0, 0, 0};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS             status;
   VXLIB_addWeight_InitArgs kerInitArgs;
   int32_t                  handleSize = VXLIB_addWeight_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle       handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsIn1, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsIn1.data_type = VXLIB_UINT8;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_UINT8;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(uint8_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   if (status == VXLIB_SUCCESS)
      status = VXLIB_addWeight_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_addWeight_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // exec checkparams
   if (status == VXLIB_SUCCESS)
      VXLIB_addWeight_exec_checkParams(handle, in0_u8, in1_u8, out_u8, alpha);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_addWeight_exec(handle, in0_u8, in1_u8, out_u8, alpha);

   printf("I_U8 I_U8 O_U8 WEIGHTED ADDITION\n");
   // print results
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%d, ", out_u8[i * width + j]);
      }
   }
   printf("\n\n");

   free(handle);

   return 0;
}
