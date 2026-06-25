// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_median.h"
#include "VXLIB_types.h"

template <typename dType>
VXLIB_STATUS VXLIB_median_MXN(VXLIB_kernelHandle handle,
                              void *restrict pIn,
                              void *restrict pMask,
                              void *restrict pOut,
                              void *restrict pScratch,
                              const int32_t trueCount);

template <typename dType>
VXLIB_STATUS VXLIB_median_MXN_UNROLL2(VXLIB_kernelHandle handle,
                                      void *restrict pIn,
                                      void *restrict pMask,
                                      void *restrict pOut,
                                      void *restrict pScratch,
                                      const int32_t trueCount);

template <typename dType>
VXLIB_STATUS VXLIB_median_MXN_UNROLL4(VXLIB_kernelHandle handle,
                                      void *restrict pIn,
                                      void *restrict pMask,
                                      void *restrict pOut,
                                      void *restrict pScratch,
                                      const int32_t trueCount);

template <typename dType>
VXLIB_STATUS VXLIB_median_MXN_UNROLL8(VXLIB_kernelHandle handle,
                                      void *restrict pIn,
                                      void *restrict pMask,
                                      void *restrict pOut,
                                      void *restrict pScratch,
                                      const int32_t trueCount);
