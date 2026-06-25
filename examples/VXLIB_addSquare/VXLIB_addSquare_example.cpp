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

    int16_t in1_i16[] = {32767, -7500, 500,
                         -5500, 150, 600,
                          400, 100, -10};
    
    int16_t out_i16[] = {0, 0, 0,
			0, 0, 0,
			0, 0, 0};
    uint8_t shift = 3;

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS             status;
   VXLIB_addSquare_InitArgs kerInitArgs;
   int32_t                  handleSize = VXLIB_addSquare_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle       handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsIn1, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsIn1.data_type = VXLIB_INT16;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(int16_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_addSquare_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_addSquare_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_addSquare_exec_checkParams(handle, in0_u8, in1_i16, out_i16, shift);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_addSquare_exec(handle, in0_u8, in1_i16, out_i16, shift);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

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
