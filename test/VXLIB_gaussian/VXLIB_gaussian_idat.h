// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_gaussian_IXX_IXX_OXX_IDAT_H
#define VXLIB_gaussian_IXX_IXX_OXX_IDAT_H

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
   size_t   width;
   size_t   height;
   size_t   filterDim;
   size_t   strideIn;
   size_t   strideOut;
   uint8_t  shift;
   size_t   padLeft;
   size_t   padRight;
   size_t   padTop;
   size_t   padBottom;
   uint32_t outputDataLocation; // 0 -> HEAP (probably L2SRAM), 1 -> MSMC
   uint32_t numReps;
   uint32_t testID;
} VXLIB_gaussian_testParams_t;

void VXLIB_gaussian_getTestParams(VXLIB_gaussian_testParams_t **params, int32_t *numTests);

#endif // VXLIB_gaussian_IXX_IXX_OXX_IDAT_H
