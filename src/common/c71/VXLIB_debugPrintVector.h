// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef COMMON_VXLIB_UTIL_DEBUGPRINTVECTOR_H_
#define COMMON_VXLIB_UTIL_DEBUGPRINTFECTOR_H_ 1

#include "../VXLIB_types.h"

//----------------------------------------------------------------------------------
#ifdef __cplusplus
#include <c7x_scalable.h> // for device scalability

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::uchar_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::uchar_vec>::value; i++) {
      VXLIB_PRINTF("%04u ", *((uchar *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::char_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::char_vec>::value; i++) {
      VXLIB_PRINTF("%04d ", *((int8_t *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::ushort_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::ushort_vec>::value; i++) {
      VXLIB_PRINTF("%05u ", *((ushort *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::short_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::short_vec>::value; i++) {
      VXLIB_PRINTF("%05d ", *((short *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::uint_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::uint_vec>::value; i++) {
      VXLIB_PRINTF("%010u ", *((uint *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::float_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::float_vec>::value; i++) {
      VXLIB_PRINTF("%f ", *((float *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::double_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::double_vec>::value; i++) {
      VXLIB_PRINTF("%lf ", *((double *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}
#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVector(c7x::int_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::int_vec>::value; i++) {
      VXLIB_PRINTF("%010d ", *((int *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintVectorInHex(c7x::long_vec vector)
{
#if VXLIB_DEBUGPRINT
   for (uint i = 0; i < c7x::element_count_of<c7x::long_vec>::value; i++) {
      VXLIB_PRINTF("%016lx ", *((long *) (&vector) + i));
   }

   VXLIB_PRINTF("%s", "\n");
#endif
}

#if __C7X_VEC_SIZE_BITS__ == 512
#pragma FUNC_ALWAYS_INLINE
static inline void VXLIB_debugPrintNonScalableVectorInHex(long8 vector)
{
#if VXLIB_DEBUGPRINT
   VXLIB_PRINTF("%010lx ", vector.s[7]);
   VXLIB_PRINTF("%010lx ", vector.s[6]);
   VXLIB_PRINTF("%010lx ", vector.s[5]);
   VXLIB_PRINTF("%010lx ", vector.s[4]);
   VXLIB_PRINTF("%010lx ", vector.s[3]);
   VXLIB_PRINTF("%010lx ", vector.s[2]);
   VXLIB_PRINTF("%010lx ", vector.s[1]);
   VXLIB_PRINTF("%010lx ", vector.s[0]);

   VXLIB_PRINTF("%s", "\n");
#endif
   return;
}
#endif

#endif //#ifdef __cplusplus
#endif /* COMMON_VXLIB_UTIL_DEBUGPRINTVECTOR_H_ */
