// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMON_VXLIB_C7X_INLINES_H_
#define COMMON_VXLIB_C7X_INLINES_H_ 1

/******************************************************************************/

/******************************************************************************/
/*!
 * \ingroup c7x_inlines
 * \brief   c7x specific inlines
 *
 * \details
 * \param
 * \return  void
 */
/******************************************************************************/

#ifdef __cplusplus
__INLINE_FUNC(c7x_permute_even_even_xxx)
template <typename dataType> static inline uchar64 c7x_permute_even_even_xxx(uchar64 permCtrl, uchar64 in1, uchar64 in0)
{
   uchar64 retVal;

   if (sizeof(dataType) == sizeof(int32_t)) {
      retVal = __permute_even_even_int(permCtrl, in1, in0);
   }
   else if (sizeof(dataType) == sizeof(int16_t)) {
      retVal = __permute_even_even_short(permCtrl, in1, in0);
   }
   else {
      retVal = (uchar64) (0);
   }
   return retVal;
}

__INLINE_FUNC(c7x_permute_odd_odd_xxx)
template <typename dataType> static inline uchar64 c7x_permute_odd_odd_xxx(uchar64 permCtrl, uchar64 in1, uchar64 in0)
{
   uchar64 retVal;

   if (sizeof(dataType) == sizeof(int32_t)) {
      retVal = __permute_odd_odd_int(permCtrl, in1, in0);
   }
   else if (sizeof(dataType) == sizeof(int16_t)) {
      retVal = __permute_odd_odd_short(permCtrl, in1, in0);
   }
   else {
      retVal = (uchar64) (0);
   }
   return retVal;
}
#endif
#endif /* COMMON_VXLIB_C7X_INLINES_H_ */
