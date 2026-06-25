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
    
    uint8_t in0_u8[] = {1, 2, 3,
			               4, 5, 6,
			               7, 8, 9};

    int16_t in1_u8[] = {9, 8, 7,
                        6, 5, 4,
                        3, 2, 1};
    
    int16_t out_u8[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS       status;
   VXLIB_and_InitArgs kerInitArgs;
   int32_t            handleSize = VXLIB_and_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle handle     = malloc(handleSize);

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
   status = VXLIB_and_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_and_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_and_exec_checkParams(handle, in0_u8, in1_u8, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_and_exec(handle, in0_u8, in1_u8, out_u8);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

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
