// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_absDiff_priv.h"
#include <cstdint>

template <typename dataType> inline dataType VXLIB_absDiff_calc_cn(dataType A, dataType B);

template <> inline uint8_t VXLIB_absDiff_calc_cn<uint8_t>(uint8_t A, uint8_t B)
{
   int16_t diff = (int16_t) A - (int16_t) B;
   uint8_t out  = (diff < 0) ? -diff : diff;
   return out;
}

template <> inline int16_t VXLIB_absDiff_calc_cn<int16_t>(int16_t A, int16_t B)
{
   int32_t diff = A - B;

   diff        = (diff < 0) ? -diff : diff;
   int16_t out = (diff > INT16_MAX) ? INT16_MAX : diff;

   return out;
}

template <typename dataType>
VXLIB_STATUS
VXLIB_absDiff_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{
   VXLIB_STATUS status = VXLIB_SUCCESS;

   VXLIB_absDiff_PrivArgs *pKerPrivArgs = (VXLIB_absDiff_PrivArgs *) handle;

   int32_t m = 0;
   int32_t n = 0;

   int32_t height    = pKerPrivArgs->height;
   int32_t width     = pKerPrivArgs->width;
   int32_t strideIn0 = pKerPrivArgs->strideIn0Elements;
   int32_t strideIn1 = pKerPrivArgs->strideIn1Elements;
   int32_t strideOut = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_absDiff_exec_cn\n");
#endif

#if VXLIB_DEBUGPRINT
   printf("VXLIB_absDiff_exec_cn: height = %d, width = %d\n", height, width);
#endif

   const dataType *restrict A = (const dataType *) pIn0;
   const dataType *restrict B = (const dataType *) pIn1;
   dataType *restrict C       = (dataType *) pOut;

   for (m = 0; m < height; m++) {
      for (n = 0; n < width; n++) {
         C[n + m * strideOut] = VXLIB_absDiff_calc_cn(A[n + m * strideIn0], B[n + m * strideIn1]);
      }
   }

   return (status);
}

template VXLIB_STATUS VXLIB_absDiff_exec_cn<uint8_t>(VXLIB_kernelHandle handle,
                                                     void *restrict pIn0,
                                                     void *restrict pIn1,
                                                     void *restrict pOut);

template VXLIB_STATUS VXLIB_absDiff_exec_cn<int16_t>(VXLIB_kernelHandle handle,
                                                     void *restrict pIn0,
                                                     void *restrict pIn1,
                                                     void *restrict pOut);
