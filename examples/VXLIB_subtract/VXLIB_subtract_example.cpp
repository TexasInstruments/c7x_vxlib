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
    
    uint8_t in0_u8[] = {22, 2, 33,
			                  4, 80, 6,
			                  100, 8, 120};

    uint8_t in1_u8[] = {11, 12, 13,
			                  41, 51, 61,
			                  72, 82, 92};

    int16_t in0_i16[] = {32767, -7500, 500,
                         -5500, 150, 600,
                          400, 100, -10};
    

    int16_t in1_i16[] = {-32768, 750, 50,
                         500, 100, 900,
                          100, 200, -1000};

    uint8_t out_u8[] = {0, 0, 0,
			                   0, 0, 0,
			                   0, 0, 0};

    int16_t out_i16[] = {0, 0, 0,
			                   0, 0, 0,
			                   0, 0, 0};

   // clang-format on

   // handles and struct for call to kernel

   VXLIB_STATUS            status;
   VXLIB_subtract_InitArgs kerInitArgs;
   int32_t                 handleSize = VXLIB_subtract_getHandleSize(&kerInitArgs);
   VXLIB_kernelHandle      handle     = malloc(handleSize);

   kerInitArgs.funcStyle      = VXLIB_FUNCTION_OPTIMIZED;
   kerInitArgs.overFlowPolicy = VXLIB_SATURATE;

   VXLIB_bufParams2D_t bufParamsIn0, bufParamsIn1, bufParamsOut;

   /* *********************************************************************************
                                   VXLIB_SUBTRACT_I8U_I8U_O8U
    *********************************************************************************** */
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

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_subtract_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_subtract_exec_checkParams(handle, in0_u8, in1_u8, out_u8);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_exec(handle, in0_u8, in1_u8, out_u8);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("Subtract in0_u8 - in1_u8 = out_u8\n");

   printf("in0_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", in0_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("in1_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", in1_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("out_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", out_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   /* *********************************************************************************
                                   VXLIB_SUBTRACT_I8U_I8U_O16S
    *********************************************************************************** */
   bufParamsIn0.data_type = VXLIB_UINT8;
   bufParamsIn0.dim_x     = width;
   bufParamsIn0.dim_y     = height;
   bufParamsIn0.stride_y  = width * sizeof(uint8_t);

   bufParamsIn1.data_type = VXLIB_UINT8;
   bufParamsIn1.dim_x     = width;
   bufParamsIn1.dim_y     = height;
   bufParamsIn1.stride_y  = width * sizeof(uint8_t);

   bufParamsOut.data_type = VXLIB_INT16;
   bufParamsOut.dim_x     = width;
   bufParamsOut.dim_y     = height;
   bufParamsOut.stride_y  = width * sizeof(int16_t);

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_subtract_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_subtract_exec_checkParams(handle, in0_u8, in1_u8, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_exec(handle, in0_u8, in1_u8, out_i16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("Subtract in0_u8 - in1_u8 = out_i16\n");

   printf("in0_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", in0_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("in1_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", in1_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("out_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", out_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   /* *********************************************************************************
                                   VXLIB_SUBTRACT_I8U_I16S_O16S
    *********************************************************************************** */

   kerInitArgs.subtractPolicy = 1; // I16S - I8U

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

   status = VXLIB_SUCCESS;

   // init checkparams
   status = VXLIB_subtract_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_subtract_exec_checkParams(handle, in0_u8, in1_i16, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_exec(handle, in0_u8, in1_i16, out_i16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("Subtract in1_u16 - in0_u8 = out_i16\n");

   printf("in0_u8:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5u, ", in0_u8[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("in1_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", in1_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("out_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", out_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   /* *********************************************************************************
                                   VXLIB_SUBTRACT_I16S_I16S_O16S
    *********************************************************************************** */

   kerInitArgs.subtractPolicy = 0;

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
   status = VXLIB_subtract_init_checkParams(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);

   // init
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_init(handle, &bufParamsIn0, &bufParamsIn1, &bufParamsOut, &kerInitArgs);
   else {
      printf("\nInit checkparams failed: %d\n", status);
      return 0;
   }

   // exec checkparams
   VXLIB_subtract_exec_checkParams(handle, in0_i16, in1_i16, out_i16);

   // exec
   if (status == VXLIB_SUCCESS)
      status = VXLIB_subtract_exec(handle, in0_i16, in1_i16, out_i16);
   else {
      printf("\nExec checkparams failed: %d\n", status);
      return 0;
   }

   // print results
   printf("Subtract in0_u16 - in1_i16 = out_i16\n");

   printf("in0_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", in0_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("in1_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", in1_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("out_i16:\n");
   for (size_t i = 0; i < height; i++) {
      for (size_t j = 0; j < width; j++) {
         printf("%5d, ", out_i16[i * width + j]);
      }
      printf("\n");
   }
   printf("\n");

   printf("----- End of subtract example -----\n");
   free(handle);

   return 0;
}
