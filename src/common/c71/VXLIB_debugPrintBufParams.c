// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "../VXLIB_types.h"
#include "VXLIB_debug.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/******************************************************************************/

/******************************************************************************/
/*!
 * \ingroup
 * \brief
 * \details
 * \return  void
 */
/******************************************************************************/

void VXLIB_debugPrintBufParams1D(const VXLIB_bufParams1D_t *params)
{
   VXLIB_PRINTF("   dim_x        = %d\n", params->dim_x);
   VXLIB_PRINTF("   data_type    = %d\n", params->data_type);

   return;
}

void VXLIB_debugPrintBufParams(const VXLIB_bufParams2D_t *params)
{
   VXLIB_PRINTF("   dim_x        = %d\n", params->dim_x);
   VXLIB_PRINTF("   dim_y        = %d\n", params->dim_y);
   VXLIB_PRINTF("   data_type    = %d\n", params->data_type);
   VXLIB_PRINTF("   stride_y     = %d\n", params->stride_y);

   return;
}

void VXLIB_debugPrintBufParams3D(const VXLIB_bufParams3D_t *params)
{
   VXLIB_PRINTF("   dim_x        = %d\n", params->dim_x);
   VXLIB_PRINTF("   dim_y        = %d\n", params->dim_y);
   VXLIB_PRINTF("   dim_z        = %d\n", params->dim_z);
   VXLIB_PRINTF("   data_type    = %d\n", params->data_type);
   VXLIB_PRINTF("   stride_y     = %d\n", params->stride_y);
   VXLIB_PRINTF("   stride_z     = %d\n", params->stride_z);

   return;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
