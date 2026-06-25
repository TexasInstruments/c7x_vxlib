// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef C71_VXLIB_UTILITY_H_
#define C71_VXLIB_UTILITY_H_ 1

#include "VXLIB_types.h"
#include <c7x.h>
#include <c7x_scalable.h>

/**
 * @brief Macros that will be useful to check for datatype combinations
 *
 */

#define VXLIB_I8U_I8U_O8U_CASE ((dTypeIn0 == VXLIB_UINT8) && (dTypeIn1 == VXLIB_UINT8) && (dTypeOut == VXLIB_UINT8))
#define VXLIB_I8S_I8S_O8S_CASE ((dTypeIn0 == VXLIB_INT8) && (dTypeIn1 == VXLIB_INT8) && (dTypeOut == VXLIB_INT8))
#define VXLIB_I8S_I8S_O8U_CASE ((dTypeIn0 == VXLIB_INT8) && (dTypeIn1 == VXLIB_INT8) && (dTypeOut == VXLIB_UINT8))
#define VXLIB_I8U_I8U_O16S_CASE ((dTypeIn0 == VXLIB_UINT8) && (dTypeIn1 == VXLIB_UINT8) && (dTypeOut == VXLIB_INT16))
#define VXLIB_I8U_I16S_O16S_CASE ((dTypeIn0 == VXLIB_UINT8) && (dTypeIn1 == VXLIB_INT16) && (dTypeOut == VXLIB_INT16))
#define VXLIB_I16S_I16S_O16S_CASE ((dTypeIn0 == VXLIB_INT16) && (dTypeIn1 == VXLIB_INT16) && (dTypeOut == VXLIB_INT16))
#define VXLIB_I16U_I16U_O16U_CASE                                                                                      \
   ((dTypeIn0 == VXLIB_UINT16) && (dTypeIn1 == VXLIB_UINT16) && (dTypeOut == VXLIB_UINT16))
#define VXLIB_I16S_I16S_O16U_CASE ((dTypeIn0 == VXLIB_INT16) && (dTypeIn1 == VXLIB_INT16) && (dTypeOut == VXLIB_UINT16))

#define VXLIB_I8U_O8U_CASE ((dTypeIn0 == VXLIB_UINT8) && (dTypeOut == VXLIB_UINT8))
#define VXLIB_I8S_O8S_CASE ((dTypeIn0 == VXLIB_INT8) && (dTypeOut == VXLIB_INT8))
#define VXLIB_I8U_O16S_CASE ((dTypeIn0 == VXLIB_UINT8) && (dTypeOut == VXLIB_INT16))
#define VXLIB_I16S_O16S_CASE ((dTypeIn0 == VXLIB_INT16) && (dTypeOut == VXLIB_INT16))
#define VXLIB_I16U_O16U_CASE ((dTypeIn0 == VXLIB_UINT16) && (dTypeOut == VXLIB_UINT16))

/**
 * @brief Macros for templatization of initialization functions
 *
 */

#define VXLIB_I8U_I8U_O8U_DTYPE VXLIB_UINT8, VXLIB_UINT8, VXLIB_UINT8
#define VXLIB_I8S_I8S_O8S_DTYPE VXLIB_INT8, VXLIB_INT8, VXLIB_INT8
#define VXLIB_I8S_I8S_O8U_DTYPE VXLIB_INT8, VXLIB_INT8, VXLIB_UINT8
#define VXLIB_I8U_I8U_O16S_DTYPE VXLIB_UINT8, VXLIB_UINT8, VXLIB_INT16
#define VXLIB_I8U_I16S_O16S_DTYPE VXLIB_UINT8, VXLIB_INT16, VXLIB_INT16
#define VXLIB_I16S_I16S_O16S_DTYPE VXLIB_INT16, VXLIB_INT16, VXLIB_INT16
#define VXLIB_I16U_I16U_O16U_DTYPE VXLIB_UINT16, VXLIB_UINT16, VXLIB_UINT16
#define VXLIB_I16S_I16S_O16U_DTYPE VXLIB_INT16, VXLIB_INT16, VXLIB_UINT16

#define VXLIB_I8U_O8U_DTYPE VXLIB_UINT8, VXLIB_UINT8
#define VXLIB_I8S_O8S_DTYPE VXLIB_INT8, VXLIB_INT8
#define VXLIB_I8U_O16S_DTYPE VXLIB_UINT8, VXLIB_INT16
#define VXLIB_I16S_O16S_DTYPE VXLIB_INT16, VXLIB_INT16
#define VXLIB_I16U_O16U_DTYPE VXLIB_UINT16, VXLIB_UINT16

template <uint32_t dTypeIn0, uint32_t dTypeIn1, uint32_t dTypeout>
size_t VXLIB_SE0SE1SA0_init(__SE_TEMPLATE_v1*          se0params,
                            __SE_TEMPLATE_v1*          se1params,
                            __SA_TEMPLATE_v1*          sa0params,
                            const VXLIB_bufParams2D_t* bufParamsIn0,
                            const VXLIB_bufParams2D_t* bufParamsIn1,
                            const VXLIB_bufParams2D_t* bufParamsOut);

template <uint32_t dTypeIn0, uint32_t dTypeout>
size_t VXLIB_SE0SA0_init(__SE_TEMPLATE_v1*          se0params,
                         __SA_TEMPLATE_v1*          sa0params,
                         const VXLIB_bufParams2D_t* bufParamsIn0,
                         const VXLIB_bufParams2D_t* bufParamsOut);

#endif /* C71_VXLIB_UTILITY_H_ */
