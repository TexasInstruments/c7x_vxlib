// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_THRESHOLDBINARY_IXX_OXX_IDAT_H
#define VXLIB_THRESHOLDBINARY_IXX_OXX_IDAT_H

#include "../common/VXLIB_test.h"
#include "VXLIB_types.h"
#include <vxlib.h>

typedef struct {
   uint8_t testPattern; /* 0: consaddt, 1: sequential, 2: random, 3: static
                           array, 4: file, etc */
   void    *staticIn;
   uint32_t dTypeIn;
   void    *staticOut;
   uint32_t dTypeOut;
   int64_t  thresholdVal;
   int64_t  trueVal;
   int64_t  falseVal;
   size_t   width;
   size_t   height;
   size_t   strideIn;
   size_t   strideOut;
   uint32_t outputDataLocation; // 0 -> HEAP (probably L2SRAM), 1 -> MSMC
   uint32_t numReps;
   uint32_t testID;
} VXLIB_thresholdBinary_testParams_t;

void VXLIB_thresholdBinary_getTestParams(VXLIB_thresholdBinary_testParams_t **params, int32_t *numTests);

#endif // VXLIB_ THRESHOLD_BINARY_IXX_OXX_IDAT_H
