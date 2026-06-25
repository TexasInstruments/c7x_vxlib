// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_bufParams.h"
#include "VXLIB_types.h"
#include "vxlib.h"
#include <cstdio>
#include <stdint.h>

/******************************************************************************/
/*                                                                            */
/* main                                                                       */
/*                                                                            */
/******************************************************************************/

int main(void)
{

   // declare image height and width dimensions
   uint32_t height, width;
   uint32_t filterWidth, filterHeight;

   /*****************************************/
   /*          Non-Padded K x K Example       */
   /*****************************************/

   // input image dimension must be greater than or equal to filter dimensions
   height       = 5;
   width        = 5;
   filterWidth  = 3;
   filterHeight = 3;

   // output image dimension calculation
   uint32_t outHeight = height - filterHeight + 1;
   uint32_t outWidth  = width - filterWidth + 1;

   // clang-format off
    
   uint8_t in_u8[] = {1,  2,  3,  4,  5,
		      6,  7,  8,  9,  10,
		      11, 12, 13, 14, 15,
		      16, 17, 18, 19, 20,
		      21, 22, 23, 24, 25};

  
   uint8_t out_u8[] = {0, 0, 0,
		       0, 0, 0,
		       0, 0, 0};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS          status;
   VXLIB_dilate_InitArgs kerInitArgs;
   int32_t               handleSize = VXLIB_dilate_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle    handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn, bufParamsOut;

   bufParamsIn.data_type = VXLIB_UINT8;
   bufParamsIn.dim_x     = width;
   bufParamsIn.dim_y     = height;
   bufParamsIn.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_UINT8;
   bufParamsOut.dim_x     = outWidth;
   bufParamsOut.dim_y     = outHeight;
   bufParamsOut.stride_y  = outWidth * sizeof(uint8_t);

   kerInitArgs.filterWidth  = filterWidth;
   kerInitArgs.filterHeight = filterHeight;

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_dilate_init_checkParams(handle, &bufParamsIn, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_dilate_init(handle, &bufParamsIn, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_dilate_exec_checkParams(handle, in_u8, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_dilate_exec(handle, in_u8, out_u8);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("\n%d x %d Dilate Filter\n", filterHeight, filterWidth);
   printf("\nInput Image\n");

   for (size_t i = 0; i < height; i++) {
      printf("\n");
      for (size_t j = 0; j < width; j++) {
         printf("%d, ", in_u8[i * width + j]);
      }
   }

   printf("\n");

   printf("\nOutput Image\n");

   for (size_t i = 0; i < outHeight; i++) {
      printf("\n");
      for (size_t j = 0; j < outWidth; j++) {
         printf("%d, ", out_u8[i * outWidth + j]);
      }
   }
   printf("\n\n");

   free(handle);

   return 0;
}
