// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#include "VXLIB_addSquare_priv.h"
#include "VXLIB_types.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* DEFINES                                                                                                            */
/*                                                                                                                    */
/**********************************************************************************************************************/

#define SE_PARAM_BASE (0x0000)
#define SE0_PARAM_OFFSET (SE_PARAM_BASE)
#define SE1_PARAM_OFFSET (SE0_PARAM_OFFSET + VXLIB_SE_PARAM_SIZE)
#define SA0_PARAM_OFFSET (SE1_PARAM_OFFSET + VXLIB_SE_PARAM_SIZE)

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_addSquare_init_ci */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method initializes the kernel-specific parameters
// mainly, the streaming engine and streaming address generators
template <uint32_t dTypeIn0, uint32_t dTypeIn1, uint32_t dTypeOut>
VXLIB_STATUS VXLIB_addSquare_init_ci(VXLIB_kernelHandle              handle,
                                     const VXLIB_bufParams2D_t      *bufParamsIn0,
                                     const VXLIB_bufParams2D_t      *bufParamsIn1,
                                     const VXLIB_bufParams2D_t      *bufParamsOut,
                                     const VXLIB_addSquare_InitArgs *pKerInitArgs)
{
   VXLIB_STATUS status = VXLIB_SUCCESS; // assign status to success by default

   // structs to hold SE and SA parameters
   __SE_TEMPLATE_v1 se0Params = __gen_SE_TEMPLATE_v1();
   __SE_TEMPLATE_v1 se1Params = __gen_SE_TEMPLATE_v1();
   __SA_TEMPLATE_v1 sa0Params = __gen_SA_TEMPLATE_v1();

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_addSquare_PrivArgs *pKerPrivArgs = (VXLIB_addSquare_PrivArgs *) handle;

   uint8_t *pBlock = pKerPrivArgs->bufPblock; // address to retrieve to store SE/SA params

   // set SE0, SE1, and SA0 params
   pKerPrivArgs->numBlocks = VXLIB_SE0SE1SA0_init<dTypeIn0, dTypeIn1, dTypeOut>(
       &se0Params, &se1Params, &sa0Params, bufParamsIn0, bufParamsIn1, bufParamsOut);

   /**************************/
   /* Store SE and SA params */
   /**************************/

   *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE0_PARAM_OFFSET) = se0Params;
   *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE1_PARAM_OFFSET) = se1Params;
   *(__SA_TEMPLATE_v1 *) ((uint8_t *) pBlock + SA0_PARAM_OFFSET) = sa0Params;

   return status;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiations for VXLIB_addSquare_init_ci */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS
VXLIB_addSquare_init_ci<VXLIB_ADDSQUARE_DTYPE_I8U_I16S_O16S>(VXLIB_kernelHandle              handle,
                                                             const VXLIB_bufParams2D_t      *bufParamsIn0,
                                                             const VXLIB_bufParams2D_t      *bufParamsIn1,
                                                             const VXLIB_bufParams2D_t      *bufParamsOut,
                                                             const VXLIB_addSquare_InitArgs *pKerInitArgs);

/**********************************************************************************************************************/
/*                                                                                                                    */
/* VXLIB_addSquare_exec_ci */
/*                                                                                                                    */
/**********************************************************************************************************************/

// this method performs pixel-wise addition of two input images
template <typename dTypeIn0, typename dTypeIn1, typename dTypeOut>
VXLIB_STATUS VXLIB_addSquare_exec_ci(VXLIB_kernelHandle handle,
                                     void *restrict pIn0,
                                     void *restrict pIn1,
                                     void *restrict pOut,
                                     uint32_t shift)
{

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_addSquare_PrivArgs *pKerPrivArgs = (VXLIB_addSquare_PrivArgs *) handle;

   // structs to retrieve SE and SA paramters
   __SE_TEMPLATE_v1 se0Params;
   __SE_TEMPLATE_v1 se1Params;
   __SA_TEMPLATE_v1 sa0Params;

   // create local pointers
   dTypeIn0 *restrict pInLocal0 = (dTypeIn0 *) pIn0;
   dTypeIn1 *restrict pInLocal1 = (dTypeIn1 *) pIn1;
   dTypeOut *restrict pOutLocal = (dTypeOut *) pOut;

#if VXLIB_DEBUGPRINT
   printf("Enter VXLIB_addSquare_exec_ci\n");
#endif

   // address of SE and SA parameters
   uint8_t *pBlock = pKerPrivArgs->bufPblock;

   // retrieve SE and SA parameters
   se0Params = *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE0_PARAM_OFFSET);
   se1Params = *(__SE_TEMPLATE_v1 *) ((uint8_t *) pBlock + SE1_PARAM_OFFSET);
   sa0Params = *(__SA_TEMPLATE_v1 *) ((uint8_t *) pBlock + SA0_PARAM_OFFSET);

   // open SEs to fetch Input samples
   __SE0_OPEN(pInLocal0, se0Params);
   __SE1_OPEN(pInLocal1, se1Params);

   // open SA0 to write output samples
   __SA0_OPEN(sa0Params);

   size_t numBlocks = pKerPrivArgs->numBlocks;

   typedef typename c7x::make_full_vector<dTypeOut>::type vec;

   c7x::int_vec vShift = (c7x::int_vec)(shift);

   for (uint32_t counter = 0; counter < numBlocks; counter++) {

      vec val0 = c7x::strm_eng<0, vec>::get_adv(); // fetch input 0 via SE0
      vec val1 = c7x::strm_eng<1, vec>::get_adv(); // fetch input 1 via SE1

      c7x::int_vec vRes0 = (0);
      c7x::int_vec vRes1 = (0);

      __vmpyhw_vvw(val0, val0, vRes0, vRes1);

      vRes0 = __vshrw_vvv(vRes0, vShift);
      vRes1 = __vshrw_vvv(vRes1, vShift);

      vec vSqr = __pack_sat(c7x::as_int_vec(vRes1), c7x::as_int_vec(vRes0));

      vec vOut = __add_sat(vSqr, val1);

      // store output via SA0
      __vpred tmp  = c7x::strm_agen<0, vec>::get_vpred();        // generate predicate
      vec    *addr = c7x::strm_agen<0, vec>::get_adv(pOutLocal); // generate address
      __vstore_pred(tmp, addr, vOut);                            // store value
   }
   // close SE/SA
   __SE0_CLOSE();
   __SE1_CLOSE();
   __SA0_CLOSE();

   return VXLIB_SUCCESS;
}

/**********************************************************************************************************************/
/*                                                                                                                    */
/* Explicit instantiations for VXLIB_addSquare_exec_ci */
/*                                                                                                                    */
/**********************************************************************************************************************/

template VXLIB_STATUS VXLIB_addSquare_exec_ci<VXLIB_ADDSQUARE_TYPENAME_I8U_I16S_O16S>(VXLIB_kernelHandle handle,
                                                                                      void *restrict pIn0,
                                                                                      void *restrict pIn1,
                                                                                      void *restrict pOut,
                                                                                      uint32_t shift);

void VXLIB_addSquare_perfEst(VXLIB_kernelHandle handle, size_t *archCycles, size_t *estCycles)
{

   // typecast handle (void) to struct pointer type associated to kernel
   VXLIB_addSquare_PrivArgs *pKerPrivArgs = (VXLIB_addSquare_PrivArgs *) handle;

   // obtain loop count for compute loop
   size_t numBlocks   = pKerPrivArgs->numBlocks;
   size_t overheadCnt = 17;                // profiled code before entering compute loop
   *archCycles        = 7 + numBlocks * 2; // obtained from asm
   *estCycles         = overheadCnt + *archCycles;
}
