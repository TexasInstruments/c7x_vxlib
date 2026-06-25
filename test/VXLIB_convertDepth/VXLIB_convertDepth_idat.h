// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_convertDepth_IXX_IXX_OXX_IDAT_H

#define VXLIB_convertDepth_IXX_IXX_OXX_IDAT_H

#include <vxlib.h>

// include test infrastructure provided by VXLIB
#include "../common/VXLIB_test.h"
#include "VXLIB_types.h"

/**
 * @brief Structure containing the parameters to run test cases for kernel
 */
typedef struct {
   /** @brief Type of test sequence data
    * 0: constant
    * 1: sequential
    * 2: sequential negative
    * 3: random
    * 4: random signed
    * 5: static
    * 6: custom
    * 7: random dimension
    * 8: random fast
    * 9: random small
    */
   uint8_t testPattern;
   /** @brief Pointer to input data 0 */
   void *staticIn0;
   /** @brief Pointer to input data 1 */
   void *staticOut;
   /** @brief Data type of input and output data */
   uint32_t dataType;
   /** @brief Height of input images */
   uint32_t width;
   /** @brief Width of input images */
   uint32_t height;
   /** @brief Stride of input images */
   uint16_t strideIn;
   /** @brief Stride of output image */
   uint16_t strideOut;
   /** @brief Stride of output image */
   uint8_t shift;
   /** @brief Overflow policy */
   VXLIB_OVERFLOW_POLICY overFlowPolicy;
   /** @brief Output location of data
    * 0: Heap (most likely L2SRAM)
    * 1: MSMC
    */
   uint32_t outputDataLocation;
   /** @brief Number of repetitions */
   uint32_t numReps;
   /** @brief Test ID */
   uint32_t testID;
} VXLIB_convertDepth_testParams_t;

void VXLIB_convertDepth_getTestParams(VXLIB_convertDepth_testParams_t **params, int32_t *numTests);

#endif /* define VXLIB_convertDepth_IXX_IXX_OXX_IDAT_H */
