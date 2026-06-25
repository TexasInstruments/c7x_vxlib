// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_median_priv.h"

/********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_median_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes median in via natural C code
template <typename dType>
VXLIB_STATUS VXLIB_median_exec_cn(VXLIB_kernelHandle handle,
                                  void *restrict pIn,
                                  void *restrict pMask,
                                  void *restrict pOut,
                                  void *restrict pScratch)
{

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_median_exec_cn\n");
#endif

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_median_PrivArgs *pKerPrivArgs = (VXLIB_median_PrivArgs *) handle;

   // obtain image parameters and overflow policy
   size_t widthOut   = pKerPrivArgs->widthOut;
   size_t heightOut  = pKerPrivArgs->heightOut;
   bool   kernelType = pKerPrivArgs->pKerInitArgs.kernelType;
   size_t M          = pKerPrivArgs->M;
   size_t N          = pKerPrivArgs->N;

   size_t strideInElements   = pKerPrivArgs->strideInElements;
   size_t strideMaskElements = pKerPrivArgs->strideMaskElements;
   size_t strideOutElements  = pKerPrivArgs->strideOutElements;

   // create local pointers
   dType *restrict pInLocal   = (dType *) pIn;
   dType *restrict pMaskLocal = (dType *) pMask;
   dType *restrict pOutLocal  = (dType *) pOut;

#if VXLIB_DEBUGPRINT
   printf("In VXLIB_median_exec_cn, widthOut: %ld, heightOut: %ld\n", widthOut, heightOut);
#endif

   if (!kernelType) {
      size_t x, y, j, k;
      dType  inWindow[9];
      for (y = 0; y < heightOut; y++) {
         for (x = 0; x < widthOut; x++) {

            /* Extract 3x3 window into stack array */
            for (j = 0; j < 3; j++) {
               for (k = 0; k < 3; k++) {
                  inWindow[j * 3 + k] = pInLocal[(y + j) * strideInElements + (x + k)];
               }
            }

            /* Sort the values in window from largest to smallest */
            for (j = 0; j < 8; j++) {
               for (k = 0; k < 8; k++) {
                  if (inWindow[k] < inWindow[k + 1]) {
                     dType tmp       = inWindow[k];
                     inWindow[k]     = inWindow[k + 1];
                     inWindow[k + 1] = tmp;
                  }
               }
            }

            /* Median is the middle value */
            pOutLocal[y * strideOutElements + x] = inWindow[4];
         }
      }
   }
   else {
      size_t x, y, j, k, cnt;
      dType  inWindow[9 * 9];
      for (y = 0; y < heightOut; y++) {
         for (x = 0; x < widthOut; x++) {

            cnt = 0;

            /* Extract MxN window into stack array */
            for (j = 0; j < M; j++) {
               for (k = 0; k < N; k++) {
                  if (pMaskLocal[j * strideMaskElements + k]) {
                     inWindow[cnt] = pInLocal[(y + j) * strideInElements + (x + k)];
                     cnt++;
                  }
               }
            }

            if (cnt > 0) {
               /* Sort the values in window from largest to smallest */
               for (j = 0; j < (cnt - 1); j++) {
                  for (k = 0; k < (cnt - 1); k++) {
                     if (inWindow[k] < inWindow[k + 1]) {
                        dType tmp       = inWindow[k];
                        inWindow[k]     = inWindow[k + 1];
                        inWindow[k + 1] = tmp;
                     }
                  }
               }

               /* Median is the middle value */
               pOutLocal[y * strideOutElements + x] = inWindow[cnt / 2];
            }
            else {
               status = VXLIB_ERR_FAILURE;
               VXLIB_DEBUGPRINTFN(0, "ERROR CN: True Count = %lu. Cannot execute kernel\n", cnt);
            }
         }
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_median_exec_cn<VXLIB_MEDIAN_TYPENAME_8U>(VXLIB_kernelHandle handle,
                                                                     void *restrict pIn,
                                                                     void *restrict pMask,
                                                                     void *restrict pOut,
                                                                     void *restrict pScratch);

template VXLIB_STATUS VXLIB_median_exec_cn<VXLIB_MEDIAN_TYPENAME_8S>(VXLIB_kernelHandle handle,
                                                                     void *restrict pIn,
                                                                     void *restrict pMask,
                                                                     void *restrict pOut,
                                                                     void *restrict pScratch);

template VXLIB_STATUS VXLIB_median_exec_cn<VXLIB_MEDIAN_TYPENAME_16U>(VXLIB_kernelHandle handle,
                                                                      void *restrict pIn,
                                                                      void *restrict pMask,
                                                                      void *restrict pOut,
                                                                      void *restrict pScratch);

template VXLIB_STATUS VXLIB_median_exec_cn<VXLIB_MEDIAN_TYPENAME_16S>(VXLIB_kernelHandle handle,
                                                                      void *restrict pIn,
                                                                      void *restrict pMask,
                                                                      void *restrict pOut,
                                                                      void *restrict pScratch);

// template VXLIB_STATUS VXLIB_median_exec_cn<VXLIB_MEDIAN_TYPENAME_64S>(VXLIB_kernelHandle handle,
//                                                                       void *restrict pIn,
//                                                                       void *restrict pMask,
//                                                                       void *restrict pOut,
//                                                                       void *restrict pScratch);
