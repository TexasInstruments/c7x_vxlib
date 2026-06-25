// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "../VXLIB_bufParams.h"
#include "../VXLIB_types.h"
#include "../VXLIB_utility.h"

//----------------------------------------------------------------------------------

template <typename dataType> void VXLIB_debugPrintMatrix_helper(dataType *matrix, const VXLIB_bufParams2D_t *params)
{
   uint32_t  x, y;
   dataType *xPtr;
   dataType *yPtr = matrix;

   // stride_y is stored in bytes, but easier to use in elements
   uint32_t stride_y_elements = params->stride_y / VXLIB_sizeof(params->data_type);

   for (y = 0; y < params->dim_y; y++) {
      xPtr = yPtr;
      VXLIB_PRINTF("%p |", xPtr);
      for (x = 0; x < params->dim_x; x++) {
         VXLIB_PRINTF("%3d ", *(xPtr));
         xPtr++;
      }
      VXLIB_PRINTF("%s", "|\n");
      yPtr += stride_y_elements;
   }

   return;
}

template void VXLIB_debugPrintMatrix_helper<int8_t>(int8_t *matrix, const VXLIB_bufParams2D_t *params);
template void VXLIB_debugPrintMatrix_helper<uint8_t>(uint8_t *matrix, const VXLIB_bufParams2D_t *params);
template void VXLIB_debugPrintMatrix_helper<int16_t>(int16_t *matrix, const VXLIB_bufParams2D_t *params);
template void VXLIB_debugPrintMatrix_helper<uint16_t>(uint16_t *matrix, const VXLIB_bufParams2D_t *params);
template void VXLIB_debugPrintMatrix_helper<int32_t>(int32_t *matrix, const VXLIB_bufParams2D_t *params);

/******************************************************************************/

// want this function to have C-linkage in library...
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void VXLIB_debugPrintMatrix(void *matrix, const VXLIB_bufParams2D_t *params)
{
   switch (params->data_type) {
   case VXLIB_INT32:
      VXLIB_debugPrintMatrix_helper<int32_t>((int32_t *) matrix, params);
      break;
   case VXLIB_INT16:
      VXLIB_debugPrintMatrix_helper<int16_t>((int16_t *) matrix, params);
      break;
   case VXLIB_UINT16:
      VXLIB_debugPrintMatrix_helper<uint16_t>((uint16_t *) matrix, params);
      break;
   case VXLIB_INT8:
      VXLIB_debugPrintMatrix_helper<int8_t>((int8_t *) matrix, params);
      break;
   case VXLIB_UINT8:
      VXLIB_debugPrintMatrix_helper<uint8_t>((uint8_t *) matrix, params);
      break;
   default:
      VXLIB_PRINTF("\nERROR: Unrecognized data type in %s.\n", __FUNCTION__);
   }

   return;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
