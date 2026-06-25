// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_tableLookup_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_tableLookup_set_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

template <typename dataType> VXLIB_STATUS VXLIB_tableLookup_set_cn(VXLIB_kernelHandle handle, void *restrict pLut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default
   // typecast handle (void) to struct pointer type associated to kernel

   return (status);
}

template VXLIB_STATUS VXLIB_tableLookup_set_cn<uint8_t>(VXLIB_kernelHandle handle, void *restrict pLut);
template VXLIB_STATUS VXLIB_tableLookup_set_cn<int8_t>(VXLIB_kernelHandle handle, void *restrict pLut);

template VXLIB_STATUS VXLIB_tableLookup_set_cn<uint16_t>(VXLIB_kernelHandle handle, void *restrict pLut);
template VXLIB_STATUS VXLIB_tableLookup_set_cn<int16_t>(VXLIB_kernelHandle handle, void *restrict pLut);

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_tableLookup_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/
template <typename dataType>
VXLIB_STATUS
VXLIB_tableLookup_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut, void *restrict pLut)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_tableLookup_exec_cn\n");
#endif

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_tableLookup_PrivArgs *pKerPrivArgs = (VXLIB_tableLookup_PrivArgs *) handle;

   // obtain image parameters
   size_t width             = pKerPrivArgs->width;
   size_t height            = pKerPrivArgs->height;
   size_t strideInElements  = pKerPrivArgs->strideInElements;
   size_t strideOutElements = pKerPrivArgs->strideOutElements;

   uint32_t count  = pKerPrivArgs->pKerInitArgs.count;
   uint16_t offset = pKerPrivArgs->pKerInitArgs.offset;

   // variables to hold temporary values
   dataType srcIndex;
   int32_t  lutIndex;

   // create local pointers
   dataType *restrict pInLocal  = (dataType *) pIn;
   dataType *restrict pOutLocal = (dataType *) pOut;
   dataType *restrict lutLocal  = (dataType *) pLut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_tableLookup_exec_cn, width: %d, height: %d\n", width, height);
#endif

   for (uint32_t i = 0; i < height; i++) {
      for (uint32_t j = 0; j < width; j++) {
         srcIndex = pInLocal[i * strideInElements + j];
         lutIndex = (int32_t) offset + (int32_t) srcIndex;
         if (lutIndex >= 0 && (uint32_t) lutIndex < count) {

            pOutLocal[i * strideOutElements + j] = lutLocal[lutIndex];
         }
         else {
            status = VXLIB_ERR_INVALID_DIMENSION;
         }
      }
   }

   return (status);
}

template VXLIB_STATUS VXLIB_tableLookup_exec_cn<uint8_t>(VXLIB_kernelHandle handle,
                                                         void *restrict pIn,
                                                         void *restrict pOut,
                                                         void *restrict pLut);
template VXLIB_STATUS VXLIB_tableLookup_exec_cn<int8_t>(VXLIB_kernelHandle handle,
                                                        void *restrict pIn,
                                                        void *restrict pOut,
                                                        void *restrict pLut);
template VXLIB_STATUS VXLIB_tableLookup_exec_cn<uint16_t>(VXLIB_kernelHandle handle,
                                                          void *restrict pIn,
                                                          void *restrict pOut,
                                                          void *restrict pLut);
template VXLIB_STATUS VXLIB_tableLookup_exec_cn<int16_t>(VXLIB_kernelHandle handle,
                                                         void *restrict pIn,
                                                         void *restrict pOut,
                                                         void *restrict pLut);
