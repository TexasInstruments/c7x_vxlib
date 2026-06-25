// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_NOT_IXX_OXX_H_
#define VXLIB_NOT_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_not VXLIB_not
 * @brief Kernel for computing bitwise not of two input vector data
 *
 *
 * @details
 *  Performs bitwise not between two images.
 *  The following datatype combinations are supported:
 *
 *  | Case    |  Input  |  Output |
 *  |  ----:  | :----:  | :----   |
 *  |    0    | uint8_t | uint8_t |
 *  |    1    |  int8_t |  int8_t |
 *  |    2    |uint16_t |uint16_t |
 *  |    3    | int16_t | int16_t |
 *
 *
 * @par Method
 * @verbatim

    dst(x,y) = ~src(x,y)

   @endverbatim
 *
 *
 * OpenVX Function Reference Page :
 https://www.khronos.org/registry/vx/specs/1.1/html/dc/d06/group__group__vision__function__not.html
 * @ingroup  VXLIB
 */

/**@{*/

/**
 * @brief Structure containing the parameters to initialize the kernel
 */

typedef struct {
   /** @brief Variant of the function, refer to @ref VXLIB_FUNCTION_STYLE     */
   int8_t funcStyle;
} VXLIB_not_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */

int32_t VXLIB_not_getHandleSize(VXLIB_not_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_not_exec function is called. This
 *               function takes care of any one-time operations such as setting
 * up the configuration of required hardware resources such as the streaming engine.  The results of these
 *               operations are stored in the handle.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn :  Pointer to the structure containing dimensional
 *                               information of input image
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output image
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 *                               parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     Application is expected to provide a valid handle.
 */

VXLIB_STATUS VXLIB_not_init(VXLIB_kernelHandle        handle,
                            VXLIB_bufParams2D_t      *bufParamsIn,
                            VXLIB_bufParams2D_t      *bufParamsOut,
                            const VXLIB_not_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_not_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_not_init, and this function
 *               must be called before the
 *               @ref VXLIB_not_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn :  Pointer to the structure containing dimensional
 *                               information of input image
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
VXLIB_not_init_checkParams(VXLIB_kernelHandle         handle,
                           const VXLIB_bufParams2D_t *bufParamsIn,
                           const VXLIB_bufParams2D_t *bufParamsOut,
                           const VXLIB_not_InitArgs  *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_not_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_not_exec, and this function
 *               must be called before the
 *               @ref VXLIB_not_exec is called.
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn   :  Pointer to the structure input image
 *  @param [out] pOut   :  Pointer to the output buffer
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     None
 */

VXLIB_STATUS VXLIB_not_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn, const void *restrict pOut);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_not_exec
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn   :  Pointer to the structure input image
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
 *               @ref VXLIB_not_init and
 *               @ref VXLIB_not_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS
VXLIB_not_exec(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

/**
 *  @brief       This function estimates the archCycles and estCycles.
 *
 *  @param [in]  handle     :  Active handle to the kernel
 *  @param [out] archCycles :  Arch compute cycles obtained from asm.
 *  @param [out] estCycles  :  Estimated cycles including overhead.
 *
 *  @return      None.
 *
 *  @par Assumptions:
 *    - None
 * *
 *  @remarks     This function is expected to be called when the estimation of cycles is needed.
 */

void VXLIB_not_perfEst(VXLIB_kernelHandle handle, size_t *archCycles, size_t *estCycles);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_NOT_IXX_OXX_H_ */
