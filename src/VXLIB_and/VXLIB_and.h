// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_AND_IXX_IXX_OXX_H_
#define VXLIB_AND_IXX_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_and VXLIB_and
 * @brief Kernel for computing bitwise and of two input vector data
 *
 *
 * @details
 *  Performs bitwise and between two images.
 *  The following datatype combinations are supported:
 *
 *  | Case    | Input0  | Input1  | Output  |
 *  |  ----:  | :----:  | :----:  | :----   |
 *  |    0    | uint8_t | uint8_t | uint8_t |
 *
 *
 * @par Method
 * @verbatim

    dst(x,y) = src0(x,y) & src1(x,y)

   @endverbatim
 *
 * @ingroup  VXLIB
 */

/**@{*/

/**
 * @brief Structure containing the parameters to initialize the kernel
 */

typedef struct {
   /** @brief Variant of the function, refer to @ref VXLIB_FUNCTION_STYLE     */
   int8_t funcStyle;
} VXLIB_and_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */

int32_t VXLIB_and_getHandleSize(VXLIB_and_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_and_exec function is called. This
 *               function takes care of any one-time operations such as setting
 * up the configuration of required hardware resources such as the streaming engine.  The results of these
 *               operations are stored in the handle.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn0 :  Pointer to the structure containing dimensional
 *                               information of input image 0
 *  @param [in]  bufParamsIn1 :  Pointer to the structure containing dimensional
 *                               information of input image 1
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output image
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 *                               parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     Application is expected to provide a valid handle.
 */

VXLIB_STATUS VXLIB_and_init(VXLIB_kernelHandle        handle,
                            VXLIB_bufParams2D_t      *bufParamsIn0,
                            VXLIB_bufParams2D_t      *bufParamsIn1,
                            VXLIB_bufParams2D_t      *bufParamsOut,
                            const VXLIB_and_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_and_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_and_init, and this function
 *               must be called before the
 *               @ref VXLIB_and_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn0 :  Pointer to the structure containing dimensional
 *                               information of input image 0
 *  @param [in]  bufParamsIn1 :  Pointer to the structure containing dimensional
 *                               information of input image 1
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output image
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 *                               parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *
 *  @remarks     None
 */

VXLIB_STATUS
VXLIB_and_init_checkParams(VXLIB_kernelHandle         handle,
                           const VXLIB_bufParams2D_t *bufParamsIn0,
                           const VXLIB_bufParams2D_t *bufParamsIn1,
                           const VXLIB_bufParams2D_t *bufParamsOut,
                           const VXLIB_and_InitArgs  *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_and_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_and_init, and this function
 *               must be called before the
 *               @ref VXLIB_and_init is called.
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn0   :  Pointer to the structure input image 0
 *  @param [in]  pIn1   :  Pointer to the structure input image 1
 *  @param [out] pOut   :  Pointer to the output buffer
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     None
 */

VXLIB_STATUS VXLIB_and_exec_checkParams(VXLIB_kernelHandle handle,
                                        const void *restrict pIn0,
                                        const void *restrict pIn1,
                                        const void *restrict pOut);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_and_exec
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn0   :  Pointer to the structure input image 0
 *  @param [in]  pIn1   :  Pointer to the structure input image 1
 *  @param [out] pOut   :  Pointer to the output buffer
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @par Assumptions:
 *    - None
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data buffers are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 *  @remarks     Before calling this function, application is expected to call
 *               @ref VXLIB_and_init and
 *               @ref VXLIB_and_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS
VXLIB_and_exec(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);

void VXLIB_and_perfEst(VXLIB_kernelHandle handle, size_t *archCycles, size_t *estCycles);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_AND_IXX_IXX_OXX_H_ */
