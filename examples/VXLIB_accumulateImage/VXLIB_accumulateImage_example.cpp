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
   
   uint8_t in0_u8[] = {51, 3, 43,
			45, 129, 53,
			253, 76, 57};

   int16_t out_i16[] = {1869, 1143, -6334,
                         -6106, -31175, 19637,
                          2403, -28473, -26501};
   VXLIB_OVERFLOW_POLICY overFlowPolicy = VXLIB_SATURATE;
   int16_t expected_out[] = {1920, 1146, -6291,
                          -6061, -31046, 19690,
                          2656, -28397, -26444};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS                   status;
   VXLIB_accumulateImage_InitArgs kerInitArgs;
   int32_t                        handleSize = VXLIB_accumulateImage_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle             handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   kerInitArgs.funcStyle      = VXLIB_FUNCTION_OPTIMIZED;
   kerInitArgs.overFlowPolicy = overFlowPolicy;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_accumulateImage_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateImage_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_accumulateImage_exec_checkParams(handle, in0_u8, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateImage_exec(handle, in0_u8, out_i16);
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
