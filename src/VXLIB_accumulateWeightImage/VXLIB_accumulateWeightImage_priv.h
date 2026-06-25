// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_ACCUMULATEWEIGHTIMAGE_IXX_OXX_PRIV_H_
#define VXLIB_ACCUMULATEWEIGHTIMAGE_IXX_OXX_PRIV_H_

#include "../common/VXLIB_utility.h"
#include "VXLIB_accumulateWeightImage.h"
#include "VXLIB_types.h"
#include <cstdint>

/**
 * @brief Macros that will be useful to check for datatype combinations
 *
 */

#define VXLIB_ACCUMULATEWEIGHTIMAGE_I8U_O8U ((dTypeIn == VXLIB_UINT8) && (dTypeOut == VXLIB_UINT8))

#endif /* VXLIB_ACCUMULATEWEIGHTIMAGE_IXX_OXX_PRIV_H_ */
