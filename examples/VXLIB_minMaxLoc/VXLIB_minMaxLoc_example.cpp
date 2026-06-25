// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_bufParams.h"
#include "VXLIB_types.h"
#include "vxlib.h"
#include <cstdio>
#include <stdint.h>

#define height (4)
#define width (4)

/******************************************************************************/
/*                                                                            */
/* main                                                                       */
/*                                                                            */
/******************************************************************************/

int main(void)
{

   // clang-format off
    
    int8_t in_s8[] = {
                      -128,   46,   34,  127,
                       -38, -128,  127,  -44,
                        12,  127, -128,    1,
                       127,   40,   35, -128,
                      };

    int8_t minVal = 127;
    int8_t maxVal = -128;

    uint32_t minCount = 0;
    uint32_t maxCount = 0;
    uint32_t minLoc[height * width * 2] = {0}; 
    uint32_t maxLoc[height * width * 2] = {0};
    uint32_t minLocCapacity = height*width;
    uint32_t maxLocCapacity = height*width;
    uint32_t startX = 0;
    uint32_t startY = 0;

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS             status;
   VXLIB_minMaxLoc_InitArgs kerInitArgs;
   int32_t                  handleSize = VXLIB_minMaxLoc_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle       handle     = malloc(handleSize);

   VXLIB_bufParams2D_t bufParamsIn;
   VXLIB_bufParams1D_t bufParamsMinLoc, bufParamsMaxLoc;

   bufParamsIn.data_type = VXLIB_INT8;
   bufParamsIn.dim_x     = width;
   bufParamsIn.dim_y     = height;
   bufParamsIn.stride_y  = width * sizeof(int8_t);

   bufParamsMinLoc.data_type = VXLIB_UINT32;
   bufParamsMinLoc.dim_x     = 2 * minLocCapacity;

   bufParamsMaxLoc.data_type = VXLIB_UINT32;
   bufParamsMaxLoc.dim_x     = 2 * maxLocCapacity;

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_minMaxLoc_init_checkParams(handle, &bufParamsIn, &bufParamsMinLoc, &bufParamsMaxLoc, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_minMaxLoc_init(handle, &bufParamsIn, &bufParamsMinLoc, &bufParamsMaxLoc, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   if (status == VXLIB_SUCCESS) {
      status = VXLIB_minMaxLoc_exec_checkParams(handle, in_s8, &minVal, &maxVal, NULL, NULL, &minLocCapacity,
                                                &maxLocCapacity, minLoc, maxLoc, &startX, &startY);
   }

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_minMaxLoc_exec(handle, in_s8, &minVal, &maxVal, &minCount, &maxCount, &minLocCapacity,
                                    &maxLocCapacity, minLoc, maxLoc, &startX, &startY);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("\n\nInput matrix:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d ", in_s8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n\n");

   printf("minVal: %d\n", minVal);
   printf("maxVal: %d\n", maxVal);
   printf("minCount: %d\n", minCount);
   printf("maxCount: %d\n", maxCount);
   printf("\n");
   printf("minLoc:\n");
   for (size_t i = 0; i < (2 * minCount); i++) {
      printf("%u, ", minLoc[i]);
   }
   printf("\n\n");

   printf("maxLoc:\n");
   for (size_t i = 0; i < (2 * maxCount); i++) {
      printf("%u, ", maxLoc[i]);
   }
   printf("\n\n");
   printf("----- End of minMaxLoc Example -----\n\n");
   free(handle);

   return 0;
}
