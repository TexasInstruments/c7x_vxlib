// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_thresholdBinary_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_thresholdBinary_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes add in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_thresholdBinary_exec_cn(VXLIB_kernelHandle handle,
                                           void *restrict pIn,
                                           void *restrict pOut,
                                           void *restrict pThresholdVal,
                                           void *restrict pTrueVal,
                                           void *restrict pFalseVal)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_thresholdBinary_PrivArgs *pKerPrivArgs = (VXLIB_thresholdBinary_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_thresholdBinary_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;
   // create local pointers
   dTypeIn *restrict pThresholdLocal = (dTypeIn *) pThresholdVal;
   dTypeIn *restrict pTrueValLocal   = (dTypeIn *) pTrueVal;
   dTypeIn *restrict pFalseValLocal  = (dTypeIn *) pFalseVal;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_thresholdBinary_exec_cn, width: %d, height: %d\n", width, height);
#endif

   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         if (pInLocal[i * strideInElements + j] > *pThresholdLocal) {
            pOutLocal[i * strideOutElements + j] = *pTrueValLocal;
         }
         else {
            pOutLocal[i * strideOutElements + j] = *pFalseValLocal;
         }
      }
   }
#if VXLIB_DEBUGPRINT
   if (i == 0 && j < 7)
      printf("row: %d col: %d a %d b %d temp %d \n", i, j, a, b, temp);
#endif

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS
VXLIB_thresholdBinary_exec_cn<VXLIB_THRESHOLDBINARY_TYPENAME_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                      void *restrict pIn,
                                                                      void *restrict pOut,
                                                                      void *restrict pThresholdVal,
                                                                      void *restrict pTrueVal,
                                                                      void *restrict pFalseVal);

template VXLIB_STATUS
VXLIB_thresholdBinary_exec_cn<VXLIB_THRESHOLDBINARY_TYPENAME_I8S_O8S>(VXLIB_kernelHandle handle,
                                                                      void *restrict pIn,
                                                                      void *restrict pOut,
                                                                      void *restrict pThresholdVal,
                                                                      void *restrict pTrueVal,
                                                                      void *restrict pFalseVal);

template VXLIB_STATUS
VXLIB_thresholdBinary_exec_cn<VXLIB_THRESHOLDBINARY_TYPENAME_I16U_O16U>(VXLIB_kernelHandle handle,
                                                                        void *restrict pIn,
                                                                        void *restrict pOut,
                                                                        void *restrict pThresholdVal,
                                                                        void *restrict pTrueVal,
                                                                        void *restrict pFalseVal);

template VXLIB_STATUS
VXLIB_thresholdBinary_exec_cn<VXLIB_THRESHOLDBINARY_TYPENAME_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                        void *restrict pIn,
                                                                        void *restrict pOut,
                                                                        void *restrict pThresholdVal,
                                                                        void *restrict pTrueVal,
                                                                        void *restrict pFalseVal);
