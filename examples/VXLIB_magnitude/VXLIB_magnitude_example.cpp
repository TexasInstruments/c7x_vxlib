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
    
   int16_t in0_i16[] = {-10283, -8783, -19686, 
                        -5435, -11371, -15561, 
                        -25816, -17409, -1916};

   int16_t in1_i16[] = {-12235, -8580, -6624, 
                        -18883, -28773, -17279, 
                        -20164, -23321, -14338};

   int16_t out_i16[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

   int16_t expected_out[] = {15982, 12278, 20771, 
                              19650, 30938, 23253, 
                              32757, 29102, 14465};

   // handles and struct for call to kernel

   VXLIB_STATUS             status;
   VXLIB_magnitude_InitArgs kerInitArgs;
   int32_t                  handleSize = VXLIB_magnitude_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle       handle     = malloc(handleSize);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsIn1, bufParamsOut;

   /* *********************************************************************************
                                   VXLIB_MAGNITUDE_I16S_I16S_O16S                          
    *********************************************************************************** */

   bufParamsIn0.data_type = VXLIB_INT16;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(int16_t);

   bufParamsIn1.data_type = VXLIB_INT16;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(int16_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_magnitude_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_magnitude_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_magnitude_exec_checkParams(handle, in0_i16, in1_i16, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_magnitude_exec(handle, in0_i16, in1_i16, out_i16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("Example of VXLIB_magnitude on 3x3 image \n");
   printf("---------------------------------\n");
   printf("|            Results            |\n");
   printf("---------------------------------\n");
   printf("|   Expected    |   Actual      |\n");
   printf("---------------------------------\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {

         printf("|   %4d\t|   %4d \t|\n", expected_out[i * width + j], out_i16[i * width + j]);
      }
   }
   printf("---------------------------------\n");

   free(handle);

   return 0;
}
