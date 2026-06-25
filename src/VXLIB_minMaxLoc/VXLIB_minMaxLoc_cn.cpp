// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_minMaxLoc_priv.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_minMaxLoc_exec_cn */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method computes add in via natural C code
template <typename dType>
VXLIB_STATUS VXLIB_minMaxLoc_exec_cn(VXLIB_kernelHandle handle,
                                     void *restrict pIn,
                                     void *restrict pMinVal,
                                     void *restrict pMaxVal,
                                     void *restrict pMinCount,
                                     void *restrict pMaxCount,
                                     void *restrict pMinLocCapacity,
                                     void *restrict pMaxLocCapacity,
                                     void *restrict pMinLoc,
                                     void *restrict pMaxLoc,
                                     void *restrict pStartX,
                                     void *restrict pStartY)
{
   VXLIB_DEBUGPRINTFN(0, "%s\n", "Entering function");

   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_minMaxLoc_PrivArgs *pKerPrivArgs = (VXLIB_minMaxLoc_PrivArgs *) handle;

   // create local pointers
   dType restrict    *pInLocal       = (dType *) pIn;
   dType restrict    *pMinValLocal   = (dType *) pMinVal;
   dType restrict    *pMaxValLocal   = (dType *) pMaxVal;
   uint32_t restrict *pMinCountLocal = (uint32_t *) pMinCount;
   uint32_t restrict *pMaxCountLocal = (uint32_t *) pMaxCount;
   uint32_t restrict *pMinLocLocal   = (uint32_t *) pMinLoc;
   uint32_t restrict *pMaxLocLocal   = (uint32_t *) pMaxLoc;
   uint32_t restrict *pStartXLocal   = (uint32_t *) pStartX;
   uint32_t restrict *pStartYLocal   = (uint32_t *) pStartY;
   uint32_t restrict *minLocCapacity = (uint32_t *) pMinLocCapacity;
   uint32_t restrict *maxLocCapacity = (uint32_t *) pMaxLocCapacity;

   // obtain dimensional parameters
   uint32_t width            = pKerPrivArgs->width;
   uint32_t height           = pKerPrivArgs->height;
   uint32_t strideInElements = pKerPrivArgs->strideInElements;
   uint32_t x, y, srcIndex;
   {
      dType    min    = *pMinValLocal;
      dType    max    = *pMaxValLocal;
      uint32_t mincnt = 0;
      uint32_t maxcnt = 0;
      if (pMinCountLocal) {
         mincnt = *pMinCountLocal;
      }
      if (pMaxCountLocal) {
         maxcnt = *pMaxCountLocal;
      }

      for (y = 0; y < height; y++) {

         for (x = 0; x < width; x++) {

            srcIndex = (y * strideInElements) + x;

            if (pInLocal[srcIndex] > max) {
               max    = pInLocal[srcIndex];
               maxcnt = 1;
               if (pMaxLocLocal) {
                  pMaxLocLocal[0] = x + (*pStartXLocal);
                  pMaxLocLocal[1] = y + (*pStartYLocal);
               }
            }
            else if (pInLocal[srcIndex] == max) {
               if (pMaxLocLocal && maxcnt < *maxLocCapacity) {
                  pMaxLocLocal[2 * maxcnt]       = x + (*pStartXLocal);
                  pMaxLocLocal[(2 * maxcnt) + 1] = y + (*pStartYLocal);
               }
               ++maxcnt;
            }
            else {
               /* Do nothing */
            }

            if (pInLocal[srcIndex] < min) {
               min    = pInLocal[srcIndex];
               mincnt = 1;
               if (pMinLocLocal) {
                  pMinLocLocal[0] = x + (*pStartXLocal);
                  pMinLocLocal[1] = y + (*pStartYLocal);
               }
            }
            else if (pInLocal[srcIndex] == min) {
               if (pMinLocLocal && mincnt < *minLocCapacity) {
                  pMinLocLocal[2 * mincnt]     = x + (*pStartXLocal);
                  pMinLocLocal[2 * mincnt + 1] = y + (*pStartYLocal);
               }
               ++mincnt;
            }
            else {
               /* Do nothing */
            }
         }
      }

      *pMinValLocal = min;
      *pMaxValLocal = max;
      if (pMinCountLocal) {
         *pMinCountLocal = mincnt;
      }
      if (pMaxCountLocal) {
         *pMaxCountLocal = maxcnt;
      }
   }

   return (status);
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiation for the different data type versions                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_minMaxLoc_exec_cn<VXLIB_MINMAXLOC_TYPENAME_8U>(VXLIB_kernelHandle handle,
                                                                           void *restrict pIn,
                                                                           void *restrict pMinVal,
                                                                           void *restrict pMaxVal,
                                                                           void *restrict pMinCount,
                                                                           void *restrict pMaxCount,
                                                                           void *restrict pMinLocCapacity,
                                                                           void *restrict pMaxLocCapacity,
                                                                           void *restrict pMinLoc,
                                                                           void *restrict pMaxLoc,
                                                                           void *restrict pStartX,
                                                                           void *restrict pStartY);

template VXLIB_STATUS VXLIB_minMaxLoc_exec_cn<VXLIB_MINMAXLOC_TYPENAME_8S>(VXLIB_kernelHandle handle,
                                                                           void *restrict pIn,
                                                                           void *restrict pMinVal,
                                                                           void *restrict pMaxVal,
                                                                           void *restrict pMinCount,
                                                                           void *restrict pMaxCount,
                                                                           void *restrict pMinLocCapacity,
                                                                           void *restrict pMaxLocCapacity,
                                                                           void *restrict pMinLoc,
                                                                           void *restrict pMaxLoc,
                                                                           void *restrict pStartX,
                                                                           void *restrict pStartY);

template VXLIB_STATUS VXLIB_minMaxLoc_exec_cn<VXLIB_MINMAXLOC_TYPENAME_16U>(VXLIB_kernelHandle handle,
                                                                            void *restrict pIn,
                                                                            void *restrict pMinVal,
                                                                            void *restrict pMaxVal,
                                                                            void *restrict pMinCount,
                                                                            void *restrict pMaxCount,
                                                                            void *restrict pMinLocCapacity,
                                                                            void *restrict pMaxLocCapacity,
                                                                            void *restrict pMinLoc,
                                                                            void *restrict pMaxLoc,
                                                                            void *restrict pStartX,
                                                                            void *restrict pStartY);

template VXLIB_STATUS VXLIB_minMaxLoc_exec_cn<VXLIB_MINMAXLOC_TYPENAME_16S>(VXLIB_kernelHandle handle,
                                                                            void *restrict pIn,
                                                                            void *restrict pMinVal,
                                                                            void *restrict pMaxVal,
                                                                            void *restrict pMinCount,
                                                                            void *restrict pMaxCount,
                                                                            void *restrict pMinLocCapacity,
                                                                            void *restrict pMaxLocCapacity,
                                                                            void *restrict pMinLoc,
                                                                            void *restrict pMaxLoc,
                                                                            void *restrict pStartX,
                                                                            void *restrict pStartY);
