// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_add_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define VXLIB_ADD_NUMERIC_MIN(x) std::numeric_limits<x>::min()
#define VXLIB_ADD_NUMERIC_MAX(x) std::numeric_limits<x>::max()

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_add_exec_cn                                                                                                  */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes add in via natural C code
template <typename dTypeIn0, typename dTypeIn1, typename dTypeOut>
VXLIB_STATUS VXLIB_add_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_add_PrivArgs *pKerPrivArgs = (VXLIB_add_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t                width             = pKerPrivArgs->width;
   size_t                height            = pKerPrivArgs->height;
   size_t                strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t                strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t                strideOutElements = pKerPrivArgs->strideOutElements;
   VXLIB_OVERFLOW_POLICY overFlowPolicy    = pKerPrivArgs->pKerInitArgs.overFlowPolicy;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_add_exec_cn\n");
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
   printf("In VXLIB_add_exec_cn, width: %d, height: %d\n", width, height);
#endif

   // perform add
   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         a = pInLocal0[i * strideIn0Elements + j];
         b = pInLocal1[i * strideIn1Elements + j];

         if (overFlowPolicy == VXLIB_SATURATE) {
            int32_t temp;
            temp = a + b;
#if VXLIB_DEBUGPRINT
            if (i == 0 && j < 7)
               printf("row: %d col: %d a %d b %d temp %d \n", i, j, a, b, temp);
#endif
            dTypeOut min = VXLIB_ADD_NUMERIC_MIN(dTypeOut);
            dTypeOut max = VXLIB_ADD_NUMERIC_MAX(dTypeOut);

            temp = (temp < min) ? min : temp;
            temp = (temp > max) ? max : temp;

            out = temp;
         }
         else {

            out = a + b;
         }

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

template VXLIB_STATUS VXLIB_add_exec_cn<VXLIB_ADD_TYPENAME_I8U_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                        void *restrict pIn0,
                                                                        void *restrict pIn1,
                                                                        void *restrict pOut);

template VXLIB_STATUS VXLIB_add_exec_cn<VXLIB_ADD_TYPENAME_I8U_I8U_O16S>(VXLIB_kernelHandle handle,
                                                                         void *restrict pIn0,
                                                                         void *restrict pIn1,
                                                                         void *restrict pOut);

template VXLIB_STATUS VXLIB_add_exec_cn<VXLIB_ADD_TYPENAME_I8U_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                          void *restrict pIn0,
                                                                          void *restrict pIn1,
                                                                          void *restrict pOut);

template VXLIB_STATUS VXLIB_add_exec_cn<VXLIB_ADD_TYPENAME_I16S_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                           void *restrict pIn0,
                                                                           void *restrict pIn1,
                                                                           void *restrict pOut);
