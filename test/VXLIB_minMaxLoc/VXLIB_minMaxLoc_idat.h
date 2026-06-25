// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_MINMAXLOC_IXX_IXX_OXX_IDAT_H
#define VXLIB_MINMAXLOC_IXX_IXX_OXX_IDAT_H

#include "../common/VXLIB_test.h"
#include "VXLIB_types.h"
#include <vxlib.h>

typedef struct {
   uint8_t testPattern; /* 0: consaddt, 1: sequential, 2: random, 3: static
                           array, 4: file, etc */
   void    *staticIn;
   uint32_t dType;
   void    *staticMinVal;
   void    *staticMaxVal;
   void    *staticMinCount;
   void    *staticMaxCount;
   void    *staticMinLoc;
   void    *staticMaxLoc;
   uint32_t width;
   uint32_t height;
   uint32_t strideIn;
   int64_t  minVal;
   int64_t  maxVal;
   uint32_t minCount;
   uint32_t maxCount;
   uint32_t minLocCapacity;
   uint32_t maxLocCapacity;
   uint32_t startX;
   uint32_t startY;
   uint16_t mode;
   uint32_t outputDataLocation; // 0 -> HEAP (probably L2SRAM), 1 -> MSMC
   uint32_t numReps;
   uint32_t testID;
} VXLIB_minMaxLoc_testParams_t;

void VXLIB_minMaxLoc_getTestParams(VXLIB_minMaxLoc_testParams_t **params, int32_t *numTests);

#endif // VXLIB_MINMAXLOC_IXX_IXX_OXX_IDAT_H
