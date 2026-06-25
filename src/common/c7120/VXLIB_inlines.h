// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef C7120_INLINES_H
#define C7120_INLINES_H

/*******************************************************************************
 *
 * Inlined functions
 *
 ******************************************************************************/

/* Horizontal Minimum */
template <typename U, typename V> static inline U VXLIB_horizontalMin(V vecIn);

template <> inline uint8_t VXLIB_horizontalMin(c7x::uchar_vec vecIn)
{
   c7x::uchar_hvec  vecMin1 = __min(vecIn.hi(), vecIn.lo());
   c7x::ushort_vec  vecMin2 = c7x::convert<c7x::ushort_vec, c7x::uchar_hvec>(vecMin1);
   c7x::ushort_vec  vecSort = __dual_sort_lo_asc_hi_asc(vecMin2);
   c7x::ushort_hvec vecMin3 = __min(vecSort.hi(), vecSort.lo());
   uint16_t         minVal  = vecMin3.s[0];
   uint8_t          minOut  = (uint8_t) (minVal);
   return minOut;
}

template <> inline int8_t VXLIB_horizontalMin(c7x::char_vec vecIn)
{
   c7x::char_hvec  vecMin1 = __min(vecIn.hi(), vecIn.lo());
   c7x::short_vec  vecMin2 = c7x::convert<c7x::short_vec, c7x::char_hvec>(vecMin1);
   c7x::short_vec  vecSort = __dual_sort_lo_asc_hi_asc(vecMin2);
   c7x::short_hvec vecMin3 = __min(vecSort.hi(), vecSort.lo());
   int16_t         minVal  = vecMin3.s[0];
   int8_t          minOut  = (int8_t) (minVal);
   return minOut;
}

template <> inline uint16_t VXLIB_horizontalMin(c7x::ushort_vec vecIn)
{
   c7x::ushort_vec  vecSort = __dual_sort_lo_asc_hi_asc(vecIn);
   c7x::ushort_hvec vecMin  = __min(vecSort.hi(), vecSort.lo());
   uint16_t         minOut  = vecMin.s[0];
   return minOut;
}

template <> inline int16_t VXLIB_horizontalMin(c7x::short_vec vecIn)
{
   c7x::short_vec  vecSort = __dual_sort_lo_asc_hi_asc(vecIn);
   c7x::short_hvec vecMin  = __min(vecSort.hi(), vecSort.lo());
   int16_t         minOut  = vecMin.s[0];
   return minOut;
}

/* Horizontal Maximum */
template <typename U, typename V> static inline U VXLIB_horizontalMax(V vecIn);

template <> inline uint8_t VXLIB_horizontalMax(c7x::uchar_vec vecIn)
{
   c7x::uchar_hvec  vecMax1 = __max(vecIn.hi(), vecIn.lo());
   c7x::ushort_vec  vecMax2 = c7x::convert<c7x::ushort_vec, c7x::uchar_hvec>(vecMax1);
   c7x::ushort_vec  vecSort = __dual_sort_lo_desc_hi_desc(vecMax2);
   c7x::ushort_hvec vecMax3 = __max(vecSort.hi(), vecSort.lo());
   uint16_t         maxVal  = vecMax3.s[0];
   uint8_t          maxOut  = (uint8_t) (maxVal);
   return maxOut;
}

template <> inline int8_t VXLIB_horizontalMax(c7x::char_vec vecIn)
{
   c7x::char_hvec  vecMax1 = __max(vecIn.hi(), vecIn.lo());
   c7x::short_vec  vecMax2 = c7x::convert<c7x::short_vec, c7x::char_hvec>(vecMax1);
   c7x::short_vec  vecSort = __dual_sort_lo_desc_hi_desc(vecMax2);
   c7x::short_hvec vecMax3 = __max(vecSort.hi(), vecSort.lo());
   int16_t         maxVal  = vecMax3.s[0];
   int8_t          maxOut  = (int8_t) (maxVal);
   return maxOut;
}

template <> inline uint16_t VXLIB_horizontalMax(c7x::ushort_vec vecIn)
{
   c7x::ushort_vec  vecSort = __dual_sort_lo_desc_hi_desc(vecIn);
   c7x::ushort_hvec vecMin  = __max(vecSort.hi(), vecSort.lo());
   uint16_t         maxOut  = vecMin.s[0];
   return maxOut;
}

template <> inline int16_t VXLIB_horizontalMax(c7x::short_vec vecIn)
{
   c7x::short_vec  vecSort = __dual_sort_lo_desc_hi_desc(vecIn);
   c7x::short_hvec vecMin  = __max(vecSort.hi(), vecSort.lo());
   int16_t         maxOut  = vecMin.s[0];
   return maxOut;
}

/******************************************************************************/

#endif
