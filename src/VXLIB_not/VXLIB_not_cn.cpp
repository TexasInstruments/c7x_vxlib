// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_not_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_not_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes not in via natural C code
template <typename dTypeIn>
VXLIB_STATUS VXLIB_not_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_not_PrivArgs *pKerPrivArgs = (VXLIB_not_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_not_exec_cn\n");
#endif

   // create local pointers
   dTypeIn *restrict pInLocal  = (dTypeIn *) pIn;
   dTypeIn *restrict pOutLocal = (dTypeIn *) pOut;

   // variable to hold temporary value
   dTypeIn a;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_not_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // using explicit casts to avoid signedness comparison warnings
   for (uint32_t i = 0; i < static_cast<uint32_t>(height); i++) {
      for (uint32_t j = 0; j < static_cast<uint32_t>(width); j++) {
         a = pInLocal[i * strideInElements + j];

         pOutLocal[i * strideOutElements + j] = ~a;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_not_exec_cn<uint8_t>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

template VXLIB_STATUS VXLIB_not_exec_cn<uint16_t>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

template VXLIB_STATUS VXLIB_not_exec_cn<int8_t>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

template VXLIB_STATUS VXLIB_not_exec_cn<int16_t>(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);
