// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_ACCUMULATESQUAREIMAGE_IXX_OXX_PRIV_H_
#define VXLIB_ACCUMULATESQUAREIMAGE_IXX_OXX_PRIV_H_

#include "../common/VXLIB_utility.h"
#include "VXLIB_accumulateSquareImage.h"
#include "VXLIB_types.h"
#include <cstdint>

/**
 * @brief Macros that will be useful to check for datatype combinations
 *
 */

#define VXLIB_ACCUMULATESQUAREIMAGE_I8U_O16S ((dTypeIn == VXLIB_UINT8) && (dTypeOut == VXLIB_INT16))

#endif /* VXLIB_ACCUMULATESQUAREIMAGE_IXX_OXX_PRIV_H_ */
