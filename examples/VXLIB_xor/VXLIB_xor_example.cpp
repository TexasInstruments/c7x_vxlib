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

    uint8_t in1_u8[] = {9, 8, 7,
                        6, 5, 4,
                        3, 2, 1};
    
    uint8_t out_u8[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

    uint16_t in0_u16[] = {1, 2, 3,
			               4, 5, 6,
			               7, 8, 9};

    uint16_t in1_u16[] = {9, 8, 7,
                        6, 5, 4,
                        3, 2, 1};
    
    uint16_t out_u16[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

    int8_t in0_s8[] = {1, 2, 3,
			               4, 5, 6,
			               7, 8, 9};

    int8_t in1_s8[] = {9, 8, 7,
                        6, 5, 4,
                        3, 2, 1};
    
    int8_t out_s8[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

    int16_t in0_s16[] = {1, 2, 3,
			               4, 5, 6,
			               7, 8, 9};

    int16_t in1_s16[] = {9, 8, 7,
                        6, 5, 4,
                        3, 2, 1};
    
    int16_t out_s16[] = {0, 0, 0,
			               0, 0, 0,
			               0, 0, 0};

   // clang-format on

   // handles and struct for call to kernel
   VXLIB_STATUS       status;
   VXLIB_xor_InitArgs kerInitArgs;
   int32_t            handleSize = VXLIB_xor_getHandleSize(&kerInitArgs);
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
   status = VXLIB_xor_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_xor_exec_checkParams(handle, in0_u8, in1_u8, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_exec(handle, in0_u8, in1_u8, out_u8);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   printf("\n UNSIGNED 8 BIT XOR \n");
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%8d, ", out_u8[i * width + j]);
      }
   }
   printf("\n\n");

   bufParamsIn0.data_type = VXLIB_UINT16;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint16_t);

   bufParamsIn1.data_type = VXLIB_UINT16;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(uint16_t);

   bufParamsOut.data_type = VXLIB_UINT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(uint16_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_xor_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_xor_exec_checkParams(handle, in0_u16, in1_u16, out_u16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_exec(handle, in0_u16, in1_u16, out_u16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   printf("\n UNSIGNED 16 BIT XOR \n");
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%8d, ", out_u16[i * width + j]);
      }
   }
   printf("\n\n");

   bufParamsIn0.data_type = VXLIB_INT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(int8_t);

   bufParamsIn1.data_type = VXLIB_INT8;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(int8_t);

   bufParamsOut.data_type = VXLIB_INT8;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int8_t);

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_xor_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_xor_exec_checkParams(handle, in0_s8, in1_s8, out_s8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_exec(handle, in0_s8, in1_s8, out_s8);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   printf("\n SIGNED 8 BIT XOR \n");
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%8d, ", out_s8[i * width + j]);
      }
   }
   printf("\n\n");

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

   kerInitArgs.funcStyle = VXLIB_FUNCTION_OPTIMIZED;

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_xor_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_xor_exec_checkParams(handle, in0_s16, in1_s16, out_s16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_xor_exec(handle, in0_s16, in1_s16, out_s16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   printf("\n SIGNED 16 - BIT XOR \n");
   for (size_t i = 0; i < height; i++) {
      printf("\n\n");
      for (size_t j = 0; j < width; j++) {
         printf("%8d, ", out_s16[i * width + j]);
      }
   }
   printf("\n\n");
   free(handle);

   return 0;
}
