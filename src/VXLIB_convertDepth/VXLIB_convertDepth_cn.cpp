// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_convertDepth_priv.h"
#include <cstdint>

template <typename dTypeIn0, typename dTypeOut>
inline dTypeOut VXLIB_convertDepth_wrap_cn(dTypeIn0 A, dTypeOut C, uint8_t shift);

inline uint8_t VXLIB_convertDepth_sat_cn(int16_t A, uint8_t shift)
{
   A = (int16_t) ((uint32_t) A >> (uint32_t) shift);

   A = A < 0 ? 0 : A;
   A = A > 255 ? 255 : A;

   uint8_t res = A;
   return res;
}

template <> inline uint8_t VXLIB_convertDepth_wrap_cn<int16_t, uint8_t>(int16_t A, uint8_t C, uint8_t shift)
{
   A = (int16_t) ((uint32_t) A >> (uint32_t) shift);

   uint8_t res = A;
   return res;
}

template <> inline int16_t VXLIB_convertDepth_wrap_cn<uint8_t, int16_t>(uint8_t A, int16_t C, uint8_t shift)
{
   int16_t res = A;

   res = (int16_t) ((uint32_t) res << (uint32_t) shift);
   return res;
}

template <typename dTypeIn0, typename dTypeOut>
VXLIB_STATUS VXLIB_convertDepth_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pOut)
{
   VXLIB_STATUS status = VXLIB_SUCCESS;

   VXLIB_convertDepth_PrivArgs *pKerPrivArgs = (VXLIB_convertDepth_PrivArgs *) handle;

   int32_t m = 0;
   int32_t n = 0;

   int32_t height    = pKerPrivArgs->height;
   int32_t width     = pKerPrivArgs->width;
   int32_t strideIn0 = pKerPrivArgs->strideIn0Elements;
   int32_t strideOut = pKerPrivArgs->strideOutElements;
   uint8_t shift     = pKerPrivArgs->shift;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_convertDepth_exec_cn\n");
#endif

#if VXLIB_DEBUGPRINT
   printf("VXLIB_convertDepth_exec_cn: height = %d, width = %d\n", height, width);
#endif

   const dTypeIn0 *restrict A = (const dTypeIn0 *) pIn0;
   dTypeOut *restrict C       = (dTypeOut *) pOut;

   if (pKerPrivArgs->overFlowPolicy == VXLIB_SATURATE) {
      for (m = 0; m < height; m++) {
         for (n = 0; n < width; n++) {
            C[n + m * strideOut] = VXLIB_convertDepth_sat_cn(A[n + m * strideIn0], shift);
         }
      }
   }
   else {
      for (m = 0; m < height; m++) {
         for (n = 0; n < width; n++) {
            C[n + m * strideOut] = VXLIB_convertDepth_wrap_cn(A[n + m * strideIn0], C[n + m * strideOut], shift);
         }
      }
   }

   return status;
}

template VXLIB_STATUS
VXLIB_convertDepth_exec_cn<int16_t, uint8_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pOut);

template VXLIB_STATUS
VXLIB_convertDepth_exec_cn<uint8_t, int16_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pOut);
