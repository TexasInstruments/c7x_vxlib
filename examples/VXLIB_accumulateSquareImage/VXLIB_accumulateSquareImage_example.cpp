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

   
   uint8_t in0_u8[] = {245, 139, 193,
			234, 93, 81,
			115, 191, 40};

   int16_t out_i16[] = {-16591, 3451, -15238,
                         -4079, -25784, 3935,
                          -32020, 29659, 5434};
   uint8_t shift = 12;

   int16_t expected_out[] = {-16577, 3455, -15229,
                         -4066, -25782, 3936,
                          -32017, 29667, 5434};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS                         status;
   VXLIB_accumulateSquareImage_InitArgs kerInitArgs;
   int32_t                              handleSize = VXLIB_accumulateSquareImage_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle                   handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_accumulateSquareImage_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateSquareImage_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_accumulateSquareImage_exec_checkParams(handle, in0_u8, out_i16, shift);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateSquareImage_exec(handle, in0_u8, out_i16, shift);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("---------------------------------\n");
   printf("|            Results            |\n");
   printf("---------------------------------\n");
   printf("|   Expected    |   Actual      |\n");
   printf("---------------------------------\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {

         printf("|   %d\t|   %d \t|\n", expected_out[i * width + j], out_i16[i * width + j]);
      }
   }
   printf("---------------------------------\n");

   free(handle);

   return 0;
}
