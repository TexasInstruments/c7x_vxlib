// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_normL1_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_normL1_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes normL1 in via natural C code
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS
VXLIB_normL1_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_normL1_PrivArgs *pKerPrivArgs = (VXLIB_normL1_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_normL1_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal0  = (dTypeIn *) pIn0;
   dTypeIn *restrict pInLocal1  = (dTypeIn *) pIn1;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

   // variables to hold temporary values

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_normL1_exec_cn, width: %d, height: %d\n", width, height);
#endif
   //  dTypeIn maxVal = std::numeric_limits<dTypeIn>::max();
   // perform normL1
   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         uint32_t absx = abs(pInLocal0[i * strideIn0Elements + j]);
         //  (abs(pInLocal0[i * strideIn0Elements + j]) > maxVal) ? maxVal : abs(pInLocal0[i * strideIn0Elements + j]);
         uint32_t absy = abs(pInLocal1[i * strideIn1Elements + j]);
         //  (abs(pInLocal1[i * strideIn1Elements + j]) > maxVal) ? maxVal : abs(pInLocal1[i * strideIn1Elements + j]);

         pOutLocal[i * strideOutElements + j] = absx + absy;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_normL1_exec_cn<VXLIB_NORML1_TYPENAME_I16S_O16U>(VXLIB_kernelHandle handle,
                                                                            void *restrict pIn0,
                                                                            void *restrict pIn1,
                                                                            void *restrict pOut);

template VXLIB_STATUS VXLIB_normL1_exec_cn<VXLIB_NORML1_TYPENAME_I8S_O8U>(VXLIB_kernelHandle handle,
                                                                          void *restrict pIn0,
                                                                          void *restrict pIn1,
                                                                          void *restrict pOut);
