// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_NOT_IXX_OXX_PRIV_H_
#define VXLIB_NOT_IXX_OXX_PRIV_H_

#include "../common/VXLIB_utility.h"
#include "VXLIB_not.h"
#include "VXLIB_types.h"
#include <cstdint>

/**
 * @brief Macro to define the size of bufPblock array of
 *        @ref VXLIB_not_PrivArgs structure.
 *
 */

#define VXLIB_NOT_IXX_OXX_PBLOCK_SIZE (VXLIB_SE_PARAM_SIZE + VXLIB_SA_PARAM_SIZE)

/**
 *  @brief This is a function pointer type that conforms to the
 *         declaration of @ref VXLIB_not_exec_ci
 *         and @ref VXLIB_not_exec_cn.
 */

typedef VXLIB_STATUS (*pFxnVXLIB_not_exec)(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

/**
 *  @brief This function is the initialization function for the C7x
 *         implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref VXLIB_not_init.
 *
 * @details This function determines the configuration for the streaming engine
 *           resources based on the function call parameters,
 *          and the configuration is saved in bufPBlock array. In the kernel
 *          call sequence, @ref VXLIB_not_exec_ci would be
 *          called later independently by the application. When
 *          @ref VXLIB_not_exec_ci runs, it merely retrieves
 *          the configuration from the bufPBlock and uses it to set up the
 *          hardware resources. This arrangement is so that
 *          @ref VXLIB_not_exec_ci does not lose cycles
 *          to determine the hardware configuration.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
 *                               information of input image 0
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output buffer
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 * parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 */

template <uint32_t dTypeIn>
extern VXLIB_STATUS VXLIB_not_init_ci(VXLIB_kernelHandle         handle,
                                      const VXLIB_bufParams2D_t *bufParamsIn,
                                      const VXLIB_bufParams2D_t *bufParamsOut,
                                      const VXLIB_not_InitArgs  *pKerInitArgs);

/**
 *  @brief This function is the main execution function for the C7x
 *         implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref VXLIB_not_exec.
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn        : Pointer to buffer holding the input image 0
 *  @param [out] pOut        : Pointer to buffer holding the output image
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data buffers are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 */

template <typename dTypeIn>
VXLIB_STATUS VXLIB_not_exec_ci(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

/**
 *  @brief This function is the main execution function for the natural
 *         C implementation of the kernel. The function declaration conforms
 *         to the declaration of @ref VXLIB_not_exec.
 *
 * @details
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn        : Pointer to buffer holding the input image 0
 *  @param [out] pOut        : Pointer to buffer holding the output image
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 */
template <typename dTypeIn>
extern VXLIB_STATUS VXLIB_not_exec_cn(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

/**
 * @brief Structure that is reserved for internal use by the kernel
 */

typedef struct {
   /** @brief Function pointer to point to the right execution variant between
    *         @ref VXLIB_not_exec_cn and
    *         @ref VXLIB_not_exec_ci.                        */
   pFxnVXLIB_not_exec execute;

   /** @brief Width of image  **/
   size_t width;
   /** @brief Height of image  **/
   size_t height;

   /** @brief Stride of input in elements **/
   size_t strideInElements;

   /** @brief Stride of output in elements **/
   size_t strideOutElements;

   /** @brief Number of blocks to be processed after simidfication **/
   size_t numBlocks;

   /** @brief Array to hold SE/SA params */
   uint8_t bufPblock[VXLIB_NOT_IXX_OXX_PBLOCK_SIZE];
} VXLIB_not_PrivArgs;

#endif /* VXLIB_NOT_IXX_OXX_PRIV_H_ */
