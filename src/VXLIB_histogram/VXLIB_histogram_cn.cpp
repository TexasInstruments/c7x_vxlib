// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_histogram_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_HISTOGRAM_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_HISTOGRAM_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_exec_cn                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/
#if defined(__C7504__) || defined(__C7524__)
// this method computes histogram in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS
VXLIB_histogram_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut, void *restrict pTemp)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t   width            = pKerPrivArgs->width;
   size_t   height           = pKerPrivArgs->height;
   size_t   strideInElements = pKerPrivArgs->strideInElements;
   uint8_t  offset           = pKerPrivArgs->pKerInitArgs.offset;
   uint16_t range            = pKerPrivArgs->pKerInitArgs.range;
   uint16_t numBins          = pKerPrivArgs->pKerInitArgs.numBins;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_histogram_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_histogram_exec_cn, width: %d, height: %d\n", width, height);
#endif
   int x, y;
   for (x = 0; x < numBins; x++) {
      pOutLocal[x] = 0;
   }

   for (y = 0; y < height; y++) {

      for (x = 0; x < width; x++) {

         uint8_t pixel = pInLocal[y * strideInElements + x];
         if ((offset <= (size_t) pixel) && ((size_t) pixel < (offset + range))) {
            size_t index = (pixel - (uint16_t) offset) * numBins / range;
            pOutLocal[index]++;
         }
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_histogram_exec_cn<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>(VXLIB_kernelHandle handle,
                                                                                 void *restrict pIn,
                                                                                 void *restrict pOut,
                                                                                 void *restrict pTemp);

#else
// this method computes histogram in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_histogram_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t   width            = pKerPrivArgs->width;
   size_t   height           = pKerPrivArgs->height;
   size_t   strideInElements = pKerPrivArgs->strideInElements;
   uint8_t  offset           = pKerPrivArgs->pKerInitArgs.offset;
   uint16_t range            = pKerPrivArgs->pKerInitArgs.range;
   uint16_t numBins          = pKerPrivArgs->pKerInitArgs.numBins;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_histogram_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_histogram_exec_cn, width: %d, height: %d\n", width, height);
#endif
   int x, y;
   for (x = 0; x < numBins; x++) {
      pOutLocal[x] = 0;
   }

   for (y = 0; y < height; y++) {

      for (x = 0; x < width; x++) {

         uint8_t pixel = pInLocal[y * strideInElements + x];
         if ((offset <= (size_t) pixel) && ((size_t) pixel < (offset + range))) {
            size_t index = (pixel - (uint16_t) offset) * numBins / range;
            pOutLocal[index]++;
         }
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_histogram_exec_cn<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>(VXLIB_kernelHandle handle,
                                                                                 void *restrict pIn,
                                                                                 void *restrict pOut);
#endif
