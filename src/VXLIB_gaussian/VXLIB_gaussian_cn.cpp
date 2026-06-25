// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_gaussian_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_GAUSSIAN_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_GAUSSIAN_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_gaussian_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/
// this method computes kxk gaussianFilter in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_gaussian_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_gaussian_exec_cn\n");
#endif

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_gaussian_PrivArgs *pKerPrivArgs = (VXLIB_gaussian_PrivArgs *) handle;

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

   size_t  filterDim = pKerPrivArgs->pKerInitArgs.filterSize;
   uint8_t shift     = pKerPrivArgs->pKerInitArgs.shift;

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_gaussian_exec_cn, width: %d, height: %d\n", width, height);
#endif

   if (filterDim == VXLIB_GAUSSIAN_FILTER_3x3) {

      // non-padded natc implementation
      if (isNotPadded) {

         int32_t x, y, i, j;
         int32_t sum;
         int32_t outWidth  = (width - filterDim + 1);
         int32_t outHeight = (height - filterDim + 1);
         int8_t  Q_BIT     = 15;

         // Creating gaussian filter 3x3 matrix
         // gaussianFilter3x3 = [[1, 2, 1], [2, 4, 2], [1, 2, 1]] * 1/16
         // Q_FACTOR = 1 << Q_BIT
         // gaussianFilter3x3 = gaussianFilter3x3 * Q_FACTOR
         int16_t gaussianFilter3x3[3][3] = {{2048, 4096, 2048}, {4096, 8192, 4096}, {2048, 4096, 2048}};

         for (y = 0; y < outHeight; y++) {
            for (x = 0; x < outWidth; x++) {

               sum = 0;

               for (j = 0; j < filterDim; j++) {
                  for (i = 0; i < filterDim; i++) {
                     sum += (pInLocal[(y + j) * strideInElements + (x + i)]) * gaussianFilter3x3[j][i];
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
   }
   // 5x5 implementation
   else if (filterDim == VXLIB_GAUSSIAN_FILTER_5x5) {
      // non-padded natc implementation
      if (isNotPadded) {

         int32_t x, y, i, j;
         int32_t sum;
         int32_t outWidth  = (width < filterDim) ? 1 : (width - filterDim + 1);
         int32_t outHeight = (height < filterDim) ? 1 : (height - filterDim + 1);

         int16_t gaussianFilter5x5[5][5] = {
             {1, 4, 6, 4, 1}, {4, 16, 24, 16, 4}, {6, 24, 36, 24, 6}, {4, 16, 24, 16, 4}, {1, 4, 6, 4, 1}};

         for (y = 0; y < outHeight; y++) {
            for (x = 0; x < outWidth; x++) {

               sum = 0;

               for (j = 0; j < filterDim; j++) {
                  for (i = 0; i < filterDim; i++) {

                     if ((y + j < height) && (x + i < width)) {
                        sum += (pInLocal[(y + j) * strideInElements + (x + i)]) * gaussianFilter5x5[j][i];
                     }
                  }
               }

               pOutLocal[y * strideOutElements + x] = (dTypeOut) ((uint32_t) sum >> (uint32_t) shift);
            }
         }
      }
      // padded natc implementation
      else {
         status = VXLIB_ERR_NOT_IMPLEMENTED;
      }
   }
   // other filter dimensions
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

template VXLIB_STATUS VXLIB_gaussian_exec_cn<VXLIB_GAUSSIAN_TYPENAME_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                              void *restrict pIn,
                                                                              void *restrict pOut);
