// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_xor_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_xor_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes xor in via natural C code
template <typename dTypeIn0>
VXLIB_STATUS VXLIB_xor_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_xor_PrivArgs *pKerPrivArgs = (VXLIB_xor_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_xor_exec_cn\n");
#endif

   // create local pointers
   dTypeIn0 *restrict pInLocal0 = (dTypeIn0 *) pIn0;
   dTypeIn0 *restrict pInLocal1 = (dTypeIn0 *) pIn1;
   dTypeIn0 *restrict pOutLocal = (dTypeIn0 *) pOut;

   // variables to hold temporary values
   dTypeIn0 a;
   dTypeIn0 b;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_xor_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // perform xor
   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         a = pInLocal0[i * strideIn0Elements + j];
         b = pInLocal1[i * strideIn1Elements + j];

         pOutLocal[i * strideOutElements + j] = a ^ b;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS
VXLIB_xor_exec_cn<uint8_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);

template VXLIB_STATUS
VXLIB_xor_exec_cn<uint16_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);

template VXLIB_STATUS
VXLIB_xor_exec_cn<int8_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);

template VXLIB_STATUS
VXLIB_xor_exec_cn<int16_t>(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);
