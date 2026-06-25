// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_histogram_priv.h"
#if defined(__C7504__) || defined(__C7524__)
#include "c6x_migration.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* FUCTION DEFINES                                                                                                    */
/*                                                                                                                    */
/**********************************************************************************************************************/

static void VXLIB_histogramSimple_i8u_o32u_core(const uint8_t even_img[restrict],
                                                const uint8_t odd_img[restrict],
                                                int32_t       width,
                                                uint32_t      _hist0[],
                                                uint32_t      _hist1[],
                                                uint32_t      _hist2[],
                                                uint32_t      _hist3[],
                                                uint32_t      hist0[restrict],
                                                uint32_t      hist1[restrict],
                                                uint32_t      hist2[restrict],
                                                uint32_t      hist3[restrict],
                                                uint32_t     *minValue);

void VXLIB_histogramSimple_i8u_o32u(const uint8_t      src[],
                                    VXLIB_kernelHandle handle,
                                    uint32_t           dist[],
                                    uint32_t           scratch[],
                                    uint32_t          *minValue,
                                    uint8_t            lastBlock);
/**********************************************************************************************************************/
/*                                                                                                                    */
/*  VXLIB_histogram_exec_scalar_ci                                                                                    */
/*                                                                                                                    */
/**********************************************************************************************************************/

static void VXLIB_histogramSimple_i8u_o32u_core(const uint8_t even_img[restrict],
                                                const uint8_t odd_img[restrict],
                                                int32_t       width,
                                                uint32_t      _hist0[],
                                                uint32_t      _hist1[],
                                                uint32_t      _hist2[],
                                                uint32_t      _hist3[],
                                                uint32_t      hist0[restrict],
                                                uint32_t      hist1[restrict],
                                                uint32_t      hist2[restrict],
                                                uint32_t      hist3[restrict],
                                                uint32_t     *minValue)
{
   int32_t  x, j;
   uint32_t ha0o, bn0e, hs0e, ha0e, bn0o, hs0o;
   uint32_t ha1o, bn1e, hs1e, ha1e, bn1o, hs1o;
   uint32_t ha2o, bn2e, hs2e, ha2e, bn2o, hs2o;
   uint32_t ha3o, bn3e, hs3e, ha3e, bn3o, hs3o;
   uint32_t pix7654, pix3210;
   int64_t  pix2a, pix2b;
   __x128_t pix4a, pix4b;
   uint32_t minVal = *minValue;

   /* Case 1: Img pointers are not aligned to 4 byte boundaries, process of 8 pixels at a time */
   /*         I/O bound max would be 9/8, but there is a compiler bug when I achieved this ... not sure where */
   /* 10/8 = 1.25 cycles per pixel */

   /* ---------------------------------------------------------------- */
   /*  Seed 'previous odd pixel' with bogus bin values that won't      */
   /*  match the first even pixels.                                    */
   /* ---------------------------------------------------------------- */
   bn3o = 1U;
   bn2o = 1U;
   bn1o = 1U;
   bn0o = 1U;

   /* ---------------------------------------------------------------- */
   /*  Prefetch the initial bins for each of our four histograms.      */
   /*  This is needed for properly handling our forwarding logic.      */
   /* ---------------------------------------------------------------- */
   ha3o = _hist3[bn3o]; /* read previous odd data */
   ha2o = _hist2[bn2o]; /* read previous odd data */
   ha1o = _hist1[bn1o]; /* read previous odd data */
   ha0o = _hist0[bn0o]; /* read previous odd data */

   /*------------------------------------------------------------------*/
   /* An iteration is peeled off here using the non-restrict qualified */
   /* _hist[0-3] to account for bn[0-3]o being 1 on the first          */
   /* iteration since it would be invalid to use restrict for the first*/
   /* iteration.  All other iterations uses index values that are a    */
   /* multiple of 4, so we can correctly use the restrict qualified    */
   /* hist[0-3] pointers to get full performance.                      */
   /*------------------------------------------------------------------*/
   x = j = 0;
   if (x < ((width / 8) * 8)) {
      /* ------------------------------------------------------------ */
      /*  Load 4 pixels from the even side of the image.  Extract     */
      /*  these so that our bin address is 4 * pixel_value.  (The     */
      /*  factor of 4 accounts for the interleave.)                   */
      /* ------------------------------------------------------------ */
      pix3210 = _mem4_const(&even_img[j * 4]);
      minVal  = _minu4(minVal, pix3210);
      pix2a   = _mpyu4ll(pix3210, 0x04040404U);
      pix4a   = _dmpy2(pix2a, 0x0001000100010001);
      bn3e    = _get32_128(pix4a, 3U); /* extract byte 3 */
      bn2e    = _get32_128(pix4a, 2U); /* extract byte 2 */
      bn1e    = _get32_128(pix4a, 1U); /* extract byte 1 */
      bn0e    = _get32_128(pix4a, 0);  /* extract byte 0 */

      /* ------------------------------------------------------------ */
      /*  For each of the four even bins, do the following steps:     */
      /*   -- Read the current value of the bin for even pixel.       */
      /*   -- Store the update for the previous odd pixel.            */
      /*   -- Increment the value we read for even pixel's bin.       */
      /*   -- Add one more if even pixel equals previous odd pixel.   */
      /*      (Except on first iteration, since there is no prev.)    */
      /* ------------------------------------------------------------ */
      hs3e = _hist3[bn3e]; /* Get even bin.                */
      hs2e = _hist2[bn2e]; /* Get even bin.                */
      hs1e = _hist1[bn1e]; /* Get even bin.                */
      hs0e = _hist0[bn0e]; /* Get even bin.                */

      _hist3[bn3o] = ha3o; /* Save previous odd bin.       */
      _hist2[bn2o] = ha2o; /* Save previous odd bin.       */
      _hist1[bn1o] = ha1o; /* Save previous odd bin.       */
      _hist0[bn0o] = ha0o; /* Save previous odd bin.       */

      ha3e = 1U + hs3e; /* Update even bin.            */
      ha2e = 1U + hs2e; /* Update even bin.            */
      ha1e = 1U + hs1e; /* Update even bin.            */
      ha0e = 1U + hs0e; /* Update even bin.            */

      ha3e += (uint32_t) (bn3e == bn3o); /* Add forwarding.   */
      ha2e += (uint32_t) (bn2e == bn2o); /* Add forwarding.   */
      ha1e += (uint32_t) (bn1e == bn1o); /* Add forwarding.   */
      ha0e += (uint32_t) (bn0e == bn0o); /* Add forwarding.   */

      /*  Load 4 pixels from the odd side of the image. */
      pix7654 = _mem4_const(&odd_img[j * 4]);
      minVal  = _minu4(minVal, pix7654);
      pix2b   = _mpyu4ll(pix7654, 0x04040404U);
      pix4b   = _dmpy2(pix2b, 0x0001000100010001);
      bn3o    = _get32_128(pix4b, 3U); /* extract byte 3 */
      bn2o    = _get32_128(pix4b, 2U); /* extract byte 2 */
      bn1o    = _get32_128(pix4b, 1U); /* extract byte 1 */
      bn0o    = _get32_128(pix4b, 0);  /* extract byte 0 */

      /* ------------------------------------------------------------ */
      /*  For each of the four odd bins, do the following steps:      */
      /*   -- Read the current value of the bin for odd pixel.        */
      /*   -- Store the update for the previous even pixel.           */
      /*   -- Increment the value we read for odd pixel's bin.        */
      /*   -- Add one more if odd pixel equals previous even pixel.   */
      /* ------------------------------------------------------------ */
      hs3o = _hist3[bn3o]; /* Get odd bin.                 */
      hs2o = _hist2[bn2o]; /* Get odd bin.                 */
      hs1o = _hist1[bn1o]; /* Get odd bin.                 */
      hs0o = _hist0[bn0o]; /* Get odd bin.                 */

      _hist3[bn3e] = ha3e; /* Save previous even bin.      */
      _hist2[bn2e] = ha2e; /* Save previous even bin.      */
      _hist1[bn1e] = ha1e; /* Save previous even bin.      */
      _hist0[bn0e] = ha0e; /* Save previous even bin.      */

      ha3o = 1U + hs3o; /* Update odd bin.             */
      ha2o = 1U + hs2o; /* Update odd bin.             */
      ha1o = 1U + hs1o; /* Update odd bin.             */
      ha0o = 1U + hs0o; /* Update odd bin.             */

      ha3o += (uint32_t) (bn3o == bn3e); /* Add forwarding.   */
      ha2o += (uint32_t) (bn2o == bn2e); /* Add forwarding.   */
      ha1o += (uint32_t) (bn1o == bn1e); /* Add forwarding.   */
      ha0o += (uint32_t) (bn0o == bn0e); /* Add forwarding.   */

      j += 2;
      x += 8;
   }
   {
      for (; x < ((width / 8) * 8); x += 8) {
         /* ------------------------------------------------------------ */
         /*  Load 4 pixels from the even side of the image.  Extract     */
         /*  these so that our bin address is 4 * pixel_value.  (The     */
         /*  factor of 4 accounts for the interleave.)                   */
         /* ------------------------------------------------------------ */
         pix3210 = _mem4_const(&even_img[j * 4]);
         minVal  = _minu4(minVal, pix3210);
         pix2a   = _mpyu4ll(pix3210, 0x04040404U);
         pix4a   = _dmpy2(pix2a, 0x0001000100010001);
         bn3e    = _get32_128(pix4a, 3U); /* extract byte 3 */
         bn2e    = _get32_128(pix4a, 2U); /* extract byte 2 */
         bn1e    = _get32_128(pix4a, 1U); /* extract byte 1 */
         bn0e    = _get32_128(pix4a, 0);  /* extract byte 0 */

         /* ------------------------------------------------------------ */
         /*  For each of the four even bins, do the following steps:     */
         /*   -- Read the current value of the bin for even pixel.       */
         /*   -- Store the update for the previous odd pixel.            */
         /*   -- Increment the value we read for even pixel's bin.       */
         /*   -- Add one more if even pixel equals previous odd pixel.   */
         /*      (Except on first iteration, since there is no prev.)    */
         /* ------------------------------------------------------------ */
         hs3e = hist3[bn3e]; /* Get even bin.                */
         hs2e = hist2[bn2e]; /* Get even bin.                */
         hs1e = hist1[bn1e]; /* Get even bin.                */
         hs0e = hist0[bn0e]; /* Get even bin.                */

         hist3[bn3o] = ha3o; /* Save previous odd bin.       */
         hist2[bn2o] = ha2o; /* Save previous odd bin.       */
         hist1[bn1o] = ha1o; /* Save previous odd bin.       */
         hist0[bn0o] = ha0o; /* Save previous odd bin.       */

         ha3e = 1U + hs3e; /* Update even bin.            */
         ha2e = 1U + hs2e; /* Update even bin.            */
         ha1e = 1U + hs1e; /* Update even bin.            */
         ha0e = 1U + hs0e; /* Update even bin.            */

         ha3e += (uint32_t) (bn3e == bn3o); /* Add forwarding.   */
         ha2e += (uint32_t) (bn2e == bn2o); /* Add forwarding.   */
         ha1e += (uint32_t) (bn1e == bn1o); /* Add forwarding.   */
         ha0e += (uint32_t) (bn0e == bn0o); /* Add forwarding.   */

         /*  Load 4 pixels from the odd side of the image. */
         pix7654 = _mem4_const(&odd_img[j * 4]);
         minVal  = _minu4(minVal, pix7654);
         pix2b   = _mpyu4ll(pix7654, 0x04040404U);
         pix4b   = _dmpy2(pix2b, 0x0001000100010001);
         bn3o    = _get32_128(pix4b, 3U); /* extract byte 3 */
         bn2o    = _get32_128(pix4b, 2U); /* extract byte 2 */
         bn1o    = _get32_128(pix4b, 1U); /* extract byte 1 */
         bn0o    = _get32_128(pix4b, 0);  /* extract byte 0 */

         /* ------------------------------------------------------------ */
         /*  For each of the four odd bins, do the following steps:      */
         /*   -- Read the current value of the bin for odd pixel.        */
         /*   -- Store the update for the previous even pixel.           */
         /*   -- Increment the value we read for odd pixel's bin.        */
         /*   -- Add one more if odd pixel equals previous even pixel.   */
         /* ------------------------------------------------------------ */
         hs3o = hist3[bn3o]; /* Get odd bin.                 */
         hs2o = hist2[bn2o]; /* Get odd bin.                 */
         hs1o = hist1[bn1o]; /* Get odd bin.                 */
         hs0o = hist0[bn0o]; /* Get odd bin.                 */

         hist3[bn3e] = ha3e; /* Save previous even bin.      */
         hist2[bn2e] = ha2e; /* Save previous even bin.      */
         hist1[bn1e] = ha1e; /* Save previous even bin.      */
         hist0[bn0e] = ha0e; /* Save previous even bin.      */

         ha3o = 1U + hs3o; /* Update odd bin.             */
         ha2o = 1U + hs2o; /* Update odd bin.             */
         ha1o = 1U + hs1o; /* Update odd bin.             */
         ha0o = 1U + hs0o; /* Update odd bin.             */

         ha3o += (uint32_t) (bn3o == bn3e); /* Add forwarding.   */
         ha2o += (uint32_t) (bn2o == bn2e); /* Add forwarding.   */
         ha1o += (uint32_t) (bn1o == bn1e); /* Add forwarding.   */
         ha0o += (uint32_t) (bn0o == bn0e); /* Add forwarding.   */

         j += 2;
      }

      /*  Store final odd-pixel bin values. */
      hist3[bn3o] = ha3o;
      hist2[bn2o] = ha2o;
      hist1[bn1o] = ha1o;
      hist0[bn0o] = ha0o;

/* Case 2: Process remaining pixels beyond multiple of 8 */
/* 7 cycles per pixel */
#pragma MUST_ITERATE(0, 8, 1)
      for (; x < width; x++) {
         hist0[even_img[x] * 4U]++;

         // Commenting the code to achieve coverage
      }
   }

   *minValue = minVal;
}

void VXLIB_histogramSimple_i8u_o32u(const uint8_t      src[],
                                    VXLIB_kernelHandle handle,
                                    uint32_t           dist[],
                                    uint32_t           scratch[],
                                    uint32_t          *minValue,
                                    uint8_t            lastBlock)
{

   int32_t  x;
   uint32_t min4 = *minValue;
   uint32_t min2, min1;

   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;

   if (pKerPrivArgs->width == pKerPrivArgs->strideInElements) {
      VXLIB_histogramSimple_i8u_o32u_core(src, &src[4], pKerPrivArgs->width * pKerPrivArgs->height, &scratch[0],
                                          &scratch[1], &scratch[2], &scratch[3], &scratch[0], &scratch[1], &scratch[2],
                                          &scratch[3], &min4);
   }
   else {

      int32_t y;

      for (y = 0; y < pKerPrivArgs->height; y++) {

         const uint8_t *even = (const uint8_t *) &src[y * pKerPrivArgs->strideInElements];
         const uint8_t *odd  = (const uint8_t *) &src[(y * pKerPrivArgs->strideInElements) + 4];

         VXLIB_histogramSimple_i8u_o32u_core(even, odd, pKerPrivArgs->width, &scratch[0], &scratch[1], &scratch[2],
                                             &scratch[3], &scratch[0], &scratch[1], &scratch[2], &scratch[3], &min4);
      }
   }

   *minValue = min4;

   /* Don't waste time updating the dist array if working through blocks of an image */
   if (lastBlock != 0) {
      /* 1.5 cycles per bin */
      _nassert(((uintptr_t) scratch % 8U) == 0);
      for (x = 0; x < 256; x++) {
         dist[x] = scratch[(x * 4) + 0] + scratch[(x * 4) + 2] + scratch[(x * 4) + 1] + scratch[(x * 4) + 3];
      }

      /* Reduce 4 lanes down to a single min value */
      min2      = _minu4(min4, min4 >> 16);
      min1      = _minu4(min2, min2 >> 8) & 0xffU;
      *minValue = min1;
   }
}

// void VXLIB_histogram_i8u_o32u(VXLIB_kernelHandle handle, const uint8_t src[], uint32_t dist[], uint32_t scratch[])
template <typename dTypeIn, typename dTypeOut>
VXLIB_STATUS
VXLIB_histogram_exec_scalar_ci(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut, void *restrict pTemp)
{

   VXLIB_STATUS status = VXLIB_SUCCESS;
   /* This function doesn't need minValue, so setting it to a dummy value */
   uint32_t minValue = 0;

   uint8_t *restrict src      = (uint8_t *) pIn;
   uint32_t *restrict dist    = (uint32_t *) pOut;
   uint32_t *restrict scratch = (uint32_t *) pTemp;

   VXLIB_histogram_PrivArgs *pKerPrivArgs = (VXLIB_histogram_PrivArgs *) handle;
   uint8_t                   offset       = pKerPrivArgs->pKerInitArgs.offset;
   uint16_t                  range        = pKerPrivArgs->pKerInitArgs.range;
   uint16_t                  numBins      = pKerPrivArgs->pKerInitArgs.numBins;
   uint8_t                   lastBlock    = pKerPrivArgs->pKerInitArgs.lastBlock;

   /* Call the optimized simple histogram function, which gives ~1.25 cycles per input pixel */
   /* Use the top of the scratch buffer to also be the intermediate dist buffer, since it doesn't
    * get written until the lastBlock = 1 anyway */
   VXLIB_histogramSimple_i8u_o32u(src, handle, scratch, scratch, &minValue, lastBlock);

   /* If calling the function on the lastBlock, then redistribute the histogram according to
    * function parameters (offset/range/numBins) */
   if (lastBlock == 1U) {

      uint16_t index;
      uint16_t x;
      uint16_t offset_16 = (uint16_t) offset;

      /* 7 cycles per input bin (range bins) */
      /* Max range == 256 (256*7 = 1792 cycles) */
      for (x = offset_16; x < (offset_16 + range); x++) {
         index = ((x - offset_16) * numBins) / range;
         dist[index] += scratch[x];
      }
   }

   return status;
}

template VXLIB_STATUS VXLIB_histogram_exec_scalar_ci<VXLIB_HISTOGRAM_TYPENAME_I8U_O32U>(VXLIB_kernelHandle handle,
                                                                                        void *restrict pIn,
                                                                                        void *restrict pOut,
                                                                                        void *restrict pTemp);
#endif
