// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_thresholdRange_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_thresholdRange_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes add in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS VXLIB_thresholdRange_exec_cn(VXLIB_kernelHandle handle,
                                          void *restrict pIn,
                                          void *restrict pOut,
                                          void *restrict pUpperVal,
                                          void *restrict pLowerVal,
                                          void *restrict pTrueVal,
                                          void *restrict pFalseVal)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_thresholdRange_PrivArgs *pKerPrivArgs = (VXLIB_thresholdRange_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_thresholdRange_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal   = (dTypeIn *) pIn;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;
   // create local pointers
   dTypeIn *restrict pUpperValLocal = (dTypeIn *) pUpperVal;
   dTypeIn *restrict pLowerValLocal = (dTypeIn *) pLowerVal;
   dTypeIn *restrict pTrueValLocal  = (dTypeIn *) pTrueVal;
   dTypeIn *restrict pFalseValLocal = (dTypeIn *) pFalseVal;
   // variables to hold temporary values

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_thresholdRange_exec_cn, width: %d, height: %d\n", width, height);
#endif

   if (*pLowerValLocal > *pUpperValLocal) {
      status = VXLIB_ERR_INVALID_VALUE;
   }
   else {

      for (uint32_t i = 0; i < height; i++) {
         for (uint32_t j = 0; j < width; j++) {
            if (pInLocal[i * strideInElements + j] > *pUpperValLocal) {
               pOutLocal[i * strideOutElements + j] = *pFalseValLocal;
            }
            else if (pInLocal[i * strideInElements + j] < *pLowerValLocal) {
               pOutLocal[i * strideOutElements + j] = *pFalseValLocal;
            }
            else {
               pOutLocal[i * strideOutElements + j] = *pTrueValLocal;
            }
         }
      }
#if VXLIB_DEBUGPRINT
      if (i == 0 && j < 7)
         printf("row: %d col: %d a %d b %d temp %d \n", i, j, a, b, temp);
#endif
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_thresholdRange_exec_cn<VXLIB_THRESHOLDRANGE_TYPENAME_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                                          void *restrict pIn,
                                                                                          void *restrict pOut,
                                                                                          void *restrict pUpperVal,
                                                                                          void *restrict pLowerVal,
                                                                                          void *restrict pTrueVal,
                                                                                          void *restrict pFalseVal);

template VXLIB_STATUS VXLIB_thresholdRange_exec_cn<VXLIB_THRESHOLDRANGE_TYPENAME_I8S_O8S>(VXLIB_kernelHandle handle,
                                                                                          void *restrict pIn,
                                                                                          void *restrict pOut,
                                                                                          void *restrict pUpperVal,
                                                                                          void *restrict pLowerVal,
                                                                                          void *restrict pTrueVal,
                                                                                          void *restrict pFalseVal);

template VXLIB_STATUS VXLIB_thresholdRange_exec_cn<VXLIB_THRESHOLDRANGE_TYPENAME_I16U_O16U>(VXLIB_kernelHandle handle,
                                                                                            void *restrict pIn,
                                                                                            void *restrict pOut,
                                                                                            void *restrict pUpperVal,
                                                                                            void *restrict pLowerVal,
                                                                                            void *restrict pTrueVal,
                                                                                            void *restrict pFalseVal);

template VXLIB_STATUS VXLIB_thresholdRange_exec_cn<VXLIB_THRESHOLDRANGE_TYPENAME_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                                            void *restrict pIn,
                                                                                            void *restrict pOut,
                                                                                            void *restrict pUpperVal,
                                                                                            void *restrict pLowerVal,
                                                                                            void *restrict pTrueVal,
                                                                                            void *restrict pFalseVal);
