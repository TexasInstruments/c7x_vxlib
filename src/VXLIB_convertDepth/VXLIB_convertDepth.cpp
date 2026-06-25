// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_bufParams.h"
#include "VXLIB_convertDepth_priv.h"

int32_t VXLIB_convertDepth_getHandleSize(VXLIB_convertDepth_InitArgs *pKerInitArgs)
{
   int32_t privBufSize = sizeof(VXLIB_convertDepth_PrivArgs);
   return privBufSize;
}

VXLIB_STATUS
VXLIB_convertDepth_init_checkParams(VXLIB_kernelHandle                 handle,
                                    const VXLIB_bufParams2D_t         *bufParamsIn0,
                                    const VXLIB_bufParams2D_t         *bufParamsOut,
                                    const VXLIB_convertDepth_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS status = VXLIB_SUCCESS;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_convertDepth_init_checkParams\n");
#endif
   if (handle == NULL || bufParamsIn0 == NULL || bufParamsOut == NULL || pKerInitArgs == NULL) {
      status = VXLIB_ERR_NULL_POINTER;
   }

   if (status == VXLIB_SUCCESS) {
      if (((bufParamsIn0->data_type != VXLIB_INT16) || (bufParamsOut->data_type != VXLIB_UINT8)) &&
          ((bufParamsIn0->data_type != VXLIB_UINT8) || (bufParamsOut->data_type != VXLIB_INT16))) {
         status = VXLIB_ERR_INVALID_TYPE;
      }
      else {
         /* Nothing to do here */
      }
   }

   if (status == VXLIB_SUCCESS) {

      if ((bufParamsIn0->dim_x != bufParamsOut->dim_x) || (bufParamsIn0->dim_y != bufParamsOut->dim_y) ||
          (bufParamsIn0->stride_y / VXLIB_sizeof(bufParamsIn0->data_type) < bufParamsIn0->dim_x) ||
          (bufParamsOut->stride_y / VXLIB_sizeof(bufParamsOut->data_type) < bufParamsOut->dim_x)) {
         status = VXLIB_ERR_INVALID_DIMENSION;
      }
   }

   return status;
}

VXLIB_STATUS
VXLIB_convertDepth_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn0, const void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_convertDepth_exec_checkParams\n");
#endif
   if ((handle == NULL) || (pIn0 == NULL) || (pOut == NULL)) {
      status = VXLIB_ERR_NULL_POINTER;
   }
   else {
      status = VXLIB_SUCCESS;
   }

   return status;
}

VXLIB_STATUS VXLIB_convertDepth_init(VXLIB_kernelHandle                 handle,
                                     VXLIB_bufParams2D_t               *bufParamsIn0,
                                     VXLIB_bufParams2D_t               *bufParamsOut,
                                     const VXLIB_convertDepth_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS                 status       = VXLIB_SUCCESS;
   VXLIB_convertDepth_PrivArgs *pKerPrivArgs = (VXLIB_convertDepth_PrivArgs *) handle;

   uint32_t height = bufParamsOut->dim_y;
   uint32_t width  = bufParamsOut->dim_x;

   // obtain buffer datatypes
   uint32_t dTypeIn0          = bufParamsIn0->data_type;
   uint32_t dTypeOut          = bufParamsOut->data_type;
   uint32_t strideIn0Elements = bufParamsIn0->stride_y / VXLIB_sizeof(dTypeIn0);
   uint32_t strideOutElements = bufParamsOut->stride_y / VXLIB_sizeof(dTypeOut);

   pKerPrivArgs->height            = height;
   pKerPrivArgs->width             = width;
   pKerPrivArgs->strideIn0Elements = strideIn0Elements;
   pKerPrivArgs->strideOutElements = strideOutElements;
   pKerPrivArgs->data_type         = dTypeIn0;

   size_t SIMD_WIDTH = VXLIB_max_simd<VXLIB_INT16>::value;

   pKerPrivArgs->shift          = pKerInitArgs->shift;
   pKerPrivArgs->overFlowPolicy = pKerInitArgs->overFlowPolicy;

   if (width == strideIn0Elements) {
      pKerPrivArgs->sePolicy = VXLIB_CONVERTDEPTH_SE_1D;
   }
   else if (width <= SIMD_WIDTH) {
      pKerPrivArgs->sePolicy = VXLIB_CONVERTDEPTH_SE_NARROW;
   }
   else {
      pKerPrivArgs->sePolicy = VXLIB_CONVERTDEPTH_SE_WIDE;
   }

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_convertDepth_init\n");
#endif

   if (pKerInitArgs->funcStyle == VXLIB_FUNCTION_NATC) {
      if (bufParamsIn0->data_type == VXLIB_UINT8) {
         pKerPrivArgs->execute = VXLIB_convertDepth_exec_cn<uint8_t, int16_t>;
      }
      else if (bufParamsIn0->data_type == VXLIB_INT16) {
         pKerPrivArgs->execute = VXLIB_convertDepth_exec_cn<int16_t, uint8_t>;
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
#if VXLIB_DEBUGPRINT
         printf("VXLIB_DEBUGPRINT  CP 2 status %d\n", status);
#endif
      }
   }
   else {
      if (bufParamsIn0->data_type == VXLIB_UINT8) {
#if VXLIB_DEBUGPRINT
         printf("VXLIB_DEBUGPRINT bufParamsIn->data_type == VXLIB_UINT8\n");
#endif
         pKerPrivArgs->execute = VXLIB_convertDepth_exec_ci<uint8_t, int16_t>;
         status =
             VXLIB_convertDepth_init_ci<VXLIB_UINT8, VXLIB_INT16>(handle, bufParamsIn0, bufParamsOut, pKerInitArgs);
      }
      else if (bufParamsIn0->data_type == VXLIB_INT16) {
         pKerPrivArgs->execute = VXLIB_convertDepth_exec_ci<int16_t, uint8_t>;
         status =
             VXLIB_convertDepth_init_ci<VXLIB_INT16, VXLIB_UINT8>(handle, bufParamsIn0, bufParamsOut, pKerInitArgs);
      }
      else {
         status = VXLIB_ERR_INVALID_TYPE;
      }
   }
#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT  CP 3 status %d\n", status);
#endif
   return status;
}

VXLIB_STATUS
VXLIB_convertDepth_exec(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pOut)
{
   VXLIB_STATUS status;

#if VXLIB_DEBUGPRINT
   printf("VXLIB_DEBUGPRINT Enter VXLIB_convertDepth_exec\n");
#endif

   VXLIB_convertDepth_PrivArgs *pKerPrivArgs = (VXLIB_convertDepth_PrivArgs *) handle;

   status = pKerPrivArgs->execute(handle, pIn0, pOut);

   return status;
}
