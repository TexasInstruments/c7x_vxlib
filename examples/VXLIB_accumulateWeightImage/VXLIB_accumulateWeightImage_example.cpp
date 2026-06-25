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

   
   uint8_t in0_u8[] = {163, 86, 220, 
                     140, 160, 83, 
                     63, 123, 200};

   uint8_t out_u8[] = {182, 0, 179, 
                     91, 45, 74, 
                     38, 213, 87};
   float alpha = 0.8831114235029028;

   uint8_t expected_out[] = {165, 75, 215, 
                           134, 146, 81, 
                           60, 133, 186};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS                         status;
   VXLIB_accumulateWeightImage_InitArgs kerInitArgs;
   int32_t                              handleSize = VXLIB_accumulateWeightImage_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle                   handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsOut;

   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_UINT8;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(uint8_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_accumulateWeightImage_init_checkParams(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateWeightImage_init(handle, &bufParamsIn0, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_accumulateWeightImage_exec_checkParams(handle, in0_u8, out_u8, alpha);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_accumulateWeightImage_exec(handle, in0_u8, out_u8, alpha);
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

         printf("|   %4d\t|   %4d \t|\n", expected_out[i * width + j], out_u8[i * width + j]);
      }
   }
   printf("---------------------------------\n");

   free(handle);

   return 0;
}
