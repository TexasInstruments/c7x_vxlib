// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_halfScaleGaussian_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_halfScaleGaussian_getHandleSize */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method calculates and returns the size of the handle for the VXLIB_halfScaleGaussian kernel
int32_t VXLIB_halfScaleGaussian_getHandleSize(VXLIB_halfScaleGaussian_InitArgs *pKerInitArgs)
{
   int32_t privBufSize = sizeof(VXLIB_halfScaleGaussian_PrivArgs);
   return privBufSize;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_halfScaleGaussian_init_checkParams */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method checks the initialization parameters for the VXLIB_halfScaleGaussian kernel
VXLIB_STATUS
VXLIB_halfScaleGaussian_init_checkParams(VXLIB_kernelHandle                      handle,
                                         const VXLIB_bufParams2D_t              *bufParamsIn,
                                         const VXLIB_bufParams2D_t              *bufParamsOut,
                                         const VXLIB_halfScaleGaussian_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS status = VXLIB_SUCCESS;

   // check for null handles
   if (handle == NULL || bufParamsIn == NULL || bufParamsOut == NULL || pKerInitArgs == NULL) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else {
      // obtain input buffer parameters
      uint32_t dTypeIn  = bufParamsIn->data_type;
      uint32_t widthIn  = bufParamsIn->dim_x;
      uint32_t heightIn = bufParamsIn->dim_y;
      uint32_t strideIn = bufParamsIn->stride_y;

      // obtain output buffer parameters
      uint32_t dTypeOut  = bufParamsOut->data_type;
      uint32_t widthOut  = bufParamsOut->dim_x;
      uint32_t heightOut = bufParamsOut->dim_y;
      uint32_t strideOut = bufParamsOut->stride_y;

      // get init arg
      size_t padLeft   = pKerInitArgs->padLeft;
      size_t padRight  = pKerInitArgs->padRight;
      size_t padTop    = pKerInitArgs->padTop;
      size_t padBottom = pKerInitArgs->padBottom;
      size_t filterDim = pKerInitArgs->filterSize;

      bool isNotPadded = (padLeft == 0) && (padRight == 0) && (padTop == 0) && (padBottom == 0);

      uint32_t strideInElements  = strideIn / VXLIB_sizeof(bufParamsIn->data_type);
      uint32_t strideOutElements = strideOut / VXLIB_sizeof(bufParamsOut->data_type);

      // check for valid datatype combinations
      if ((dTypeIn != VXLIB_UINT8) || (dTypeOut != VXLIB_UINT8)) {
         status = VXLIB_ERR_INVALID_TYPE;
      }

      // disqualify padded implementation
      else if (!isNotPadded) {
         status = VXLIB_ERR_NOT_IMPLEMENTED;
      }

      // check valid dimensions; input height, width must be greater, equal to filter size for non padded implementation
      else if ((widthIn < ((widthOut + 2) * 2)) || (heightIn != ((heightOut + 2) * 2)) ||
               (strideInElements < widthIn) || (strideOutElements < widthOut) || (widthIn < filterDim) ||
               (heightIn < filterDim)) {
         status = VXLIB_ERR_INVALID_DIMENSION;
      }

      else {
         status = VXLIB_SUCCESS;
      }
   }
   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_halfScaleGaussian_exec_checkParams */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method checks the execution parameters for the VXLIB_halfScaleGaussian kernel
VXLIB_STATUS
VXLIB_halfScaleGaussian_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn, const void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_halfScaleGaussian_exec_checkParams\n");
#endif
   if ((handle == NULL) || (pIn == NULL) || (pOut == NULL)) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else {
      status = VXLIB_SUCCESS;
   }

   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_halfScaleGaussian_init */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method is the user-level initialization function for the VXLIB_halfScaleGaussian kernel
VXLIB_STATUS VXLIB_halfScaleGaussian_init(VXLIB_kernelHandle                      handle,
                                          VXLIB_bufParams2D_t                    *bufParamsIn,
                                          VXLIB_bufParams2D_t                    *bufParamsOut,
                                          const VXLIB_halfScaleGaussian_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS                      status       = VXLIB_SUCCESS;
   VXLIB_halfScaleGaussian_PrivArgs *pKerPrivArgs = (VXLIB_halfScaleGaussian_PrivArgs *) handle;

   // copy pKerinitArgs into pKerPrivargs
   pKerPrivArgs->pKerInitArgs = *pKerInitArgs;

   // set priv args
   pKerPrivArgs->widthIn   = bufParamsIn->dim_x;
   pKerPrivArgs->heightIn  = bufParamsIn->dim_y;
   pKerPrivArgs->widthOut  = bufParamsOut->dim_x;
   pKerPrivArgs->heightOut = bufParamsOut->dim_y;

   // compute stride in elements as SE/SA params are set to work with given element type
   pKerPrivArgs->strideInElements  = bufParamsIn->stride_y / VXLIB_sizeof(bufParamsIn->data_type);
   pKerPrivArgs->strideOutElements = bufParamsOut->stride_y / VXLIB_sizeof(bufParamsOut->data_type);

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_halfScaleGaussian_init\n");
#endif

   // obtain buffer datatypes
   uint32_t dTypeIn  = bufParamsIn->data_type;
   uint32_t dTypeOut = bufParamsOut->data_type;

   // determine natural C  vs optimized function call
   if (pKerInitArgs->funcStyle == VXLIB_FUNCTION_NATC) {

      // set function pointer for natural C function with appropriate template parameters based on datatypes

      if (VXLIB_HALF_SCALE_GAUSSIAN_I8U_O8U) {
         pKerPrivArgs->execute = VXLIB_halfScaleGaussian_exec_cn<VXLIB_HALF_SCALE_GAUSSIAN_TYPENAME_I8U_O8U>;
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
      }
   }
   else { // Optimized function

      // set function pointer for natural C function with appropriate template parameters based on datatypes

      if (VXLIB_HALF_SCALE_GAUSSIAN_I8U_O8U) {
         status = VXLIB_halfScaleGaussian_init_ci<VXLIB_HALF_SCALE_GAUSSIAN_DTYPE_I8U_O8U>(handle, bufParamsIn,
                                                                                           bufParamsOut, pKerInitArgs);
         pKerPrivArgs->execute = VXLIB_halfScaleGaussian_exec_ci<VXLIB_HALF_SCALE_GAUSSIAN_TYPENAME_I8U_O8U>;
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
      }
   }

   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_halfScaleGaussian_exec */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method is the user-level execution function for the VXLIB_halfScaleGaussian kernel
VXLIB_STATUS
VXLIB_halfScaleGaussian_exec(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_halfScaleGaussian_exec\n");
#endif

   VXLIB_halfScaleGaussian_PrivArgs *pKerPrivArgs = (VXLIB_halfScaleGaussian_PrivArgs *) handle;

   status = pKerPrivArgs->execute(handle, pIn, pOut);

   return status;
}
