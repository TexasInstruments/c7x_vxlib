// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "../VXLIB_bufParams.h"
#include "../VXLIB_types.h"

/******************************************************************************/

template <typename dataType> void VXLIB_debugPrint3DVReg_helper(dataType *matrix, const VXLIB_bufParams3D_t *params)
{
   uint32_t  r, c, t;
   dataType *xPtr;
   dataType *yPtr;
   dataType *zPtr = matrix;

   // stride_y is stored in bytes, but easier to use in elements
   uint32_t stride_y_elements = params->stride_y / VXLIB_sizeof(params->data_type);
   uint32_t stride_z_elements = params->stride_z / VXLIB_sizeof(params->data_type);

   VXLIB_PRINTF("%s", "{\n");
   for (t = 0; t < params->dim_z; t++) {
      yPtr = zPtr;
      for (r = 0; r < params->dim_y; r++) {
         xPtr = yPtr;
         for (c = 0; c < params->dim_x; c++) {
            VXLIB_PRINTF("%3d, ", *(xPtr));
            xPtr++;
         }
         VXLIB_PRINTF("%s", "\n");
         yPtr += stride_y_elements;
      }
      zPtr += stride_z_elements;
   }
   VXLIB_PRINTF("%s", "};\n");
   return;
}

template void VXLIB_debugPrint3DVReg_helper<int8_t>(int8_t *matrix, const VXLIB_bufParams3D_t *params);
template void VXLIB_debugPrint3DVReg_helper<int16_t>(int16_t *matrix, const VXLIB_bufParams3D_t *params);
template void VXLIB_debugPrint3DVReg_helper<uint16_t>(uint16_t *matrix, const VXLIB_bufParams3D_t *params);
template void VXLIB_debugPrint3DVReg_helper<int32_t>(int32_t *matrix, const VXLIB_bufParams3D_t *params);

/******************************************************************************/

// want this function to have C-linkage in library...
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void VXLIB_debugPrint3DVReg(void *matrix, const VXLIB_bufParams3D_t *params)
{
   switch (params->data_type) {
   case VXLIB_INT32:
      VXLIB_debugPrint3DVReg_helper<int32_t>((int32_t *) matrix, params);
      break;
   case VXLIB_INT16:
      VXLIB_debugPrint3DVReg_helper<int16_t>((int16_t *) matrix, params);
      break;
   case VXLIB_UINT16:
      VXLIB_debugPrint3DVReg_helper<uint16_t>((uint16_t *) matrix, params);
      break;
   case VXLIB_INT8:
      VXLIB_debugPrint3DVReg_helper<int8_t>((int8_t *) matrix, params);
      break;
   default:
      VXLIB_PRINTF("\nERROR: Unrecognized data type in %s.\n", __FUNCTION__);
   }

   return;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
