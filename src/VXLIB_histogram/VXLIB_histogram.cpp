// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_histogram_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_getHandleSize                                                                                      */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method calculates and returns the size of the handle for the VXLIB_histogram kernel
int32_t VXLIB_histogram_getHandleSize(VXLIB_histogram_InitArgs *pKerInitArgs)
{
   int32_t privBufSize = sizeof(VXLIB_histogram_PrivArgs);
   return privBufSize;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_init_checkParams */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method checks the initialization parameters for the VXLIB_histogram kernel
VXLIB_STATUS
VXLIB_histogram_init_checkParams(VXLIB_kernelHandle              handle,
                                 const VXLIB_bufParams2D_t      *bufParamsIn,
                                 const VXLIB_bufParams1D_t      *bufParamsOut,
                                 const VXLIB_histogram_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS status = VXLIB_SUCCESS;

   // obtain input0 buffer parameters
   uint32_t dTypeIn  = bufParamsIn->data_type;
   uint32_t widthIn  = bufParamsIn->dim_x;
   uint32_t strideIn = bufParamsIn->stride_y;

   // obtain output buffer parameters
   uint32_t dTypeOut = bufParamsOut->data_type;

   uint8_t  offset    = pKerInitArgs->offset;
   uint16_t range     = pKerInitArgs->range;
   uint16_t numBins   = pKerInitArgs->numBins;
   uint8_t  lastBlock = pKerInitArgs->lastBlock;

   // check for dimensions and datatype combinations
   if (handle == NULL) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else if (!(VXLIB_HISTOGRAM_I8U_O32U)) {
      status = VXLIB_ERR_INVALID_TYPE;
   }
   else if ((strideIn < widthIn)) {
      status = VXLIB_ERR_INVALID_DIMENSION;
   }
   else if (((offset + range) > VXLIB_HISTOGRAM_MAX_PIXEL_VALUE) || (numBins > VXLIB_HISTOGRAM_MAX_PIXEL_VALUE)) {
      status = VXLIB_ERR_INVALID_VALUE;
   }
   else if ((lastBlock != 0) && (lastBlock != 1)) {
      status = VXLIB_ERR_INVALID_VALUE;
   }
   else {
      status = VXLIB_SUCCESS;
   }

   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_exec_checkParams */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method checks the execution parameters for the VXLIB_histogram kernel
#if defined(__C7504__) || defined(__C7524__)
VXLIB_STATUS
VXLIB_histogram_exec_checkParams(VXLIB_kernelHandle handle,
                                 const void *restrict pIn,
                                 const void *restrict pOut,
                                 const void *restrict pTemp)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_histogram_exec_checkParams\n");
#endif
   if ((handle == NULL) || (pIn == NULL) || (pOut == NULL) || (pTemp == NULL)) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else {
      status = VXLIB_SUCCESS;
   }

   return status;
}
#else // C7120 and C7100
VXLIB_STATUS
VXLIB_histogram_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn, const void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_histogram_exec_checkParams\n");
#endif
   if ((handle == NULL) || (pIn == NULL) || (pOut == NULL)) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else {
      status = VXLIB_SUCCESS;
   }

   return status;
}
#endif

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_init */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method is the user-level initialization function for the VXLIB_histogram kernel
VXLIB_STATUS VXLIB_histogram_init(VXLIB_kernelHandle              handle,
                                  VXLIB_bufParams2D_t            *bufParamsIn,
                                  VXLIB_bufParams1D_t            *bufParamsOut,
                                  const VXLIB_histogram_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS              status       = VXLIB_SUCCESS;
   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   // copy pKerinitArgs into pKerPrivargs
   pKerPrivArgs->pKerInitArgs = *pKerInitArgs;

   // set width and height of image
   pKerPrivArgs->width  = bufParamsIn->dim_x;
   pKerPrivArgs->height = bufParamsIn->dim_y;

   // compute stride in elements as SE/SA params are set to work with given element type
   pKerPrivArgs->strideInElements = bufParamsIn->stride_y / VXLIB_sizeof(bufParamsIn->data_type);

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_histogram_init\n");
#endif

   // obtain buffer datatypes
   uint32_t dTypeIn  = bufParamsIn->data_type;
   uint32_t dTypeOut = bufParamsOut->data_type;

   // determine natural C  vs optimized function call
   if (pKerInitArgs->funcStyle == VXLIB_FUNCTION_NATC) {
      if (VXLIB_HISTOGRAM_I8U_O32U) {
         pKerPrivArgs->execute = VXLIB_histogram_exec_cn<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>;
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
      }
   }
   else { // Optimized function
      if (VXLIB_HISTOGRAM_I8U_O32U) {
#if !defined(__C7504__) && !defined(__C7524__)
         status =
             VXLIB_histogram_init_ci<VXLIB_HISTOGRAM_DTYPE_I8U_O32U>(handle, bufParamsIn, bufParamsOut, pKerInitArgs);
         pKerPrivArgs->execute = VXLIB_histogram_exec_ci<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>;
#elif defined(__C7504__) || defined(__C7524__)
         pKerPrivArgs->execute = VXLIB_histogram_exec_scalar_ci<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>;
#endif
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
      }
   }

   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_histogram_exec */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method is the user-level execution function for the VXLIB_histogram kernel
#if !defined(__C7504__) && !defined(__C7524__)
VXLIB_STATUS
VXLIB_histogram_exec(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_histogram_exec\n");
#endif

   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   status = pKerPrivArgs->execute(handle, pIn, pOut);

   return status;
}
#elif defined(__C7504__) || defined(__C7524__)
VXLIB_STATUS
VXLIB_histogram_exec(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut, void *restrict pTemp)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_histogram_exec\n");
#endif

   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   status = pKerPrivArgs->execute(handle, pIn, pOut, pTemp);

   return status;
}
#endif
