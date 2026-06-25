// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_multiply_priv.h"
/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_multiply_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes multiply in via natural C code

template <typename dTypeIn0, typename dTypeIn1, typename dTypeOut>
VXLIB_STATUS
VXLIB_multiply_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut)
{
   VXLIB_DEBUGPRINTFN(0, "%s\n", "Enter Function");
   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   typedef typename c7x::make_full_vector<dTypeIn0>::type vec;
   typedef
       typename std::conditional<ELEM_COUNT(c7x::uchar_vec) == ELEM_COUNT(vec), int32_t, int64_t>::type typeResultInt;

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_multiply_PrivArgs *pKerPrivArgs = (VXLIB_multiply_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t                width             = pKerPrivArgs->width;
   size_t                height            = pKerPrivArgs->height;
   size_t                strideIn0Elements = pKerPrivArgs->strideIn0Elements;
   size_t                strideIn1Elements = pKerPrivArgs->strideIn1Elements;
   size_t                strideOutElements = pKerPrivArgs->strideOutElements;
   VXLIB_OVERFLOW_POLICY overFlowPolicy    = pKerPrivArgs->pKerInitArgs.overFlowPolicy;
   VXLIB_F32             scale             = pKerPrivArgs->pKerInitArgs.scale;

   // create local pointers
   dTypeIn0 *restrict pInLocal0 = (dTypeIn0 *) pIn0;
   dTypeIn1 *restrict pInLocal1 = (dTypeIn1 *) pIn1;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

   // variables to hold temporary values
   uint32_t      x, y, src0Index, src1Index, dstIndex;
   int32_t       unscaledIntResult, finalResult;
   typeResultInt scaledIntResult;
   VXLIB_D64     unscaledDoubleResult, scaledDoubleResut;

   {
      for (y = 0; y < height; y++) {

         for (x = 0; x < width; x++) {
            src0Index = y * strideIn0Elements + x;
            src1Index = y * strideIn1Elements + x;
            dstIndex  = y * strideOutElements + x;

            unscaledIntResult    = pInLocal0[src0Index] * pInLocal1[src1Index];
            unscaledDoubleResult = (double) unscaledIntResult;
            scaledDoubleResut    = scale * unscaledDoubleResult;

            scaledIntResult = (typeResultInt) scaledDoubleResut;

            /* Finally, overflow-check as per the target type and policy. */
            if (overFlowPolicy == VXLIB_SATURATE) {
               if (scaledIntResult > VXLIB_MULTIPLY_NUMERIC_MAX(dTypeOut)) {
                  finalResult = VXLIB_MULTIPLY_NUMERIC_MAX(dTypeOut);
               }
               else if (scaledIntResult < VXLIB_MULTIPLY_NUMERIC_MIN(dTypeOut)) {
                  finalResult = VXLIB_MULTIPLY_NUMERIC_MIN(dTypeOut);
               }
               else {
                  finalResult = (dTypeOut) scaledIntResult;
               }
            }
            else {
               /* Just for show: the final assignment will wrap too. */
               finalResult = (dTypeOut) scaledIntResult;
            }
            pOutLocal[dstIndex] = (dTypeOut) finalResult;
         }
      }
   }

   VXLIB_DEBUGPRINTFN(0, "%s\n", "Exit Function");
   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_multiply_exec_cn<VXLIB_MULTIPLY_TYPENAME_I8U_I8U_O8U>(VXLIB_kernelHandle handle,
                                                                                  void *restrict pIn0,
                                                                                  void *restrict pIn1,
                                                                                  void *restrict pOut);

template VXLIB_STATUS VXLIB_multiply_exec_cn<VXLIB_MULTIPLY_TYPENAME_I8U_I8U_O16S>(VXLIB_kernelHandle handle,
                                                                                   void *restrict pIn0,
                                                                                   void *restrict pIn1,
                                                                                   void *restrict pOut);

template VXLIB_STATUS VXLIB_multiply_exec_cn<VXLIB_MULTIPLY_TYPENAME_I8U_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                                    void *restrict pIn0,
                                                                                    void *restrict pIn1,
                                                                                    void *restrict pOut);

template VXLIB_STATUS VXLIB_multiply_exec_cn<VXLIB_MULTIPLY_TYPENAME_I16S_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                                     void *restrict pIn0,
                                                                                     void *restrict pIn1,
                                                                                     void *restrict pOut);
