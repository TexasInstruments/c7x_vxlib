// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_addWeight_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_addWeight_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes addWeight in via natural C code
template <typename dTypeIn0, typename dTypeIn1, typename dTypeOut>
VXLIB_STATUS VXLIB_addWeight_exec_cn(VXLIB_kernelHandle handle,
                                     void *restrict pIn0,
                                     void *restrict pIn1,
                                     void *restrict pOut,
                                     float alpha)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_addWeight_PrivArgs *pKerPrivArgs = (VXLIB_addWeight_PrivArgs *) handle;

   // obtain image parameters
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_addWeight_exec_cn\n");
#endif

   // create local pointers
   dTypeIn0 *restrict pInLocal0 = (dTypeIn0 *) pIn0;
   dTypeIn1 *restrict pInLocal1 = (dTypeIn1 *) pIn1;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

   // variables to hold temporary values
   dTypeIn0 a;
   dTypeIn1 b;
   dTypeOut out;

   // float containers for computation values
   float a_, b_, out_;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_addWeight_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // perform addWeight
   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         a = pInLocal0[i * strideIn0Elements + j];
         b = pInLocal1[i * strideIn1Elements + j];

         // move to float containers for computation
         a_   = (float) (int32_t) a;
         b_   = (float) (int32_t) b;
         out_ = alpha * a_ + (1 - alpha) * b_;

         // move back to uint8_t container
         out = (dTypeOut) (int8_t) out_;

         pOutLocal[i * strideOutElements + j] = out;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_addWeight_exec_cn<VXLIB_ADDWEIGHT_TYPENAME_I8U_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                                    void *restrict pIn0,
                                                                                    void *restrict pIn1,
                                                                                    void *restrict pOut,
                                                                                    float alpha);
