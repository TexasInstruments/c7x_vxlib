// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_dilate_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_DILATE_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_DILATE_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_dilate_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes M x N dilate via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_dilate_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_dilate_exec_cn\n");
#endif

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_dilate_PrivArgs *pKerPrivArgs = (VXLIB_dilate_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

   size_t filterWidth  = pKerPrivArgs->pKerInitArgs.filterWidth;
   size_t filterHeight = pKerPrivArgs->pKerInitArgs.filterHeight;

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_dilate_exec_cn, width: %d, height: %d\n", width, height);
#endif

   int32_t x, y, i, j;
   dTypeIn max_val;
   int32_t outWidth  = (width - filterWidth + 1);
   int32_t outHeight = (height - filterHeight + 1);

   for (x = 0; x < outHeight; x++) {
      for (y = 0; y < outWidth; y++) {

         max_val = 0;

         // Cast size_t to int32_t for comparison to avoid signedness warnings
         for (i = 0; i < static_cast<int32_t>(filterHeight); i++) {
            for (j = 0; j < static_cast<int32_t>(filterWidth); j++) {

               max_val = std::max((pInLocal[(x + i) * strideInElements + (y + j)]), max_val);
            }
         }

         pOutLocal[x * strideOutElements + y] = max_val;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS
VXLIB_dilate_exec_cn<VXLIB_DILATE_TYPENAME_I8U_O8U>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

template VXLIB_STATUS VXLIB_dilate_exec_cn<VXLIB_DILATE_TYPENAME_I16U_O16U>(VXLIB_kernelHandle handle,
                                                                            void *restrict pIn,
                                                                            void *restrict pOut);
