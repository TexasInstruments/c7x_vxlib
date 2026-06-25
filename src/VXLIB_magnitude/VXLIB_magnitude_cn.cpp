// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_magnitude_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_MAGNITUDE_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_MAGNITUDE_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_magnitude_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes add in via natural C code
template <typename dTypeIn0, typename dTypeIn1, typename dTypeOut>
VXLIB_STATUS
VXLIB_magnitude_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_magnitude_PrivArgs *pKerPrivArgs = (VXLIB_magnitude_PrivArgs *) handle;

   // obtain image parameters
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_magnitude_exec_cn\n");
#endif

   // create local pointers
   dTypeIn0 *restrict pInLocal0 = (dTypeIn0 *) pIn0;
   dTypeIn1 *restrict pInLocal1 = (dTypeIn1 *) pIn1;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

   // variables to hold temporary values
   dTypeIn0 a;
   dTypeIn1 b;
   dTypeOut out;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_magnitude_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // max values for saturation clip
   dTypeOut max = VXLIB_MAGNITUDE_NUMERIC_MAX(dTypeOut);
   // perform add
   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         a = pInLocal0[i * strideIn0Elements + j];
         b = pInLocal1[i * strideIn1Elements + j];

         int32_t a_sqr;
         int32_t b_sqr;
         int32_t sum_sqr;
         int32_t temp;

         a_sqr   = a * a;
         b_sqr   = b * b;
         sum_sqr = a_sqr + b_sqr;

         temp = (int32_t) (sqrt(sum_sqr) + 0.5);

         temp = (temp > max) ? max : temp;

         out = temp;

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

template VXLIB_STATUS VXLIB_magnitude_exec_cn<VXLIB_MAGNITUDE_TYPENAME_I16S_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                                       void *restrict pIn0,
                                                                                       void *restrict pIn1,
                                                                                       void *restrict pOut);
