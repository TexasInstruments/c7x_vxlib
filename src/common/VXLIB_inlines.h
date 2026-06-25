// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMON_INLINES_H
#define COMMON_INLINES_H

#include "VXLIB_types.h"
#include <float.h>  // for max float, double values
#include <limits.h> // for min, max integer values

#if defined(__C7100__) || defined(__C7120__) || defined(__C7502__) || defined(__C7504__) || defined(__C7508__) ||      \
    defined(__C7524__)
#include "c71/VXLIB_inlines.h"
#else
#error invalid target
#endif

#if defined(__C7100__)
#include "c7100/VXLIB_inlines.h"
#endif

#if defined(__C7120__)
#include "c7120/VXLIB_inlines.h"
#endif

#if defined(__C7502__)
#include "c7502/VXLIB_inlines.h"
#endif

#if defined(__C7504__)
#include "c7504/VXLIB_inlines.h"
#endif

#if defined(__C7508__)
#include "c7508/VXLIB_inlines.h"
#endif

#if defined(__C7524__)
#include "c7524/VXLIB_inlines.h"
#endif
/******************************************************************************/

#endif
