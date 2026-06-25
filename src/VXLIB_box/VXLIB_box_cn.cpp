// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_box_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_BOX_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_BOX_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_box_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/
// this method computes kxk boxFilter in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_box_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_box_exec_cn\n");
#endif

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_box_PrivArgs *pKerPrivArgs = (VXLIB_box_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

   size_t padLeft     = pKerPrivArgs->pKerInitArgs.padLeft;
   size_t padRight    = pKerPrivArgs->pKerInitArgs.padRight;
   size_t padTop      = pKerPrivArgs->pKerInitArgs.padTop;
   size_t padBottom   = pKerPrivArgs->pKerInitArgs.padBottom;
   bool   isNotPadded = (padLeft == 0) && (padRight == 0) && (padTop == 0) && (padBottom == 0);

   size_t filterDim = pKerPrivArgs->pKerInitArgs.filterSize;

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_box_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // non-padded natc implementation
   if (isNotPadded) {

      int32_t x, y, i, j;
      int32_t sum;
      int32_t outWidth   = (width - filterDim + 1);
      int32_t outHeight  = (height - filterDim + 1);
      float   spCoeff    = 1.0 / (filterDim * filterDim);
      int8_t  Q_BIT      = 15;
      int32_t Q_FACTOR   = (int32_t) (1u << (uint32_t) Q_BIT);
      int16_t fixedCoeff = spCoeff * Q_FACTOR;

      for (y = 0; y < outHeight; y++) {
         for (x = 0; x < outWidth; x++) {

            sum = 0;

            for (j = 0; j < filterDim; j++) {
               for (i = 0; i < filterDim; i++) {

                  sum += (pInLocal[(y + j) * strideInElements + (x + i)]) * fixedCoeff;
               }
            }

            pOutLocal[y * strideOutElements + x] = (dTypeOut) ((uint32_t) sum >> (uint32_t) Q_BIT);
         }
      }
   }

   // padded natc implementation
   else {
      status = VXLIB_ERR_NOT_IMPLEMENTED;
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS
VXLIB_box_exec_cn<VXLIB_BOX_TYPENAME_I8U_O8U>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);
