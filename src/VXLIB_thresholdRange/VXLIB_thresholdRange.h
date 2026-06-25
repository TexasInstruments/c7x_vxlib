// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_THRESHOLDRANGE_IXX_OXX_H_
#define VXLIB_THRESHOLDRANGE_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_thresholdRange VXLIB_thresholdRange
 * @brief Kernel for Thresholding an  input image and produces an  output Boolean image.
 *
 *
 * @details
 *  Performs thresholdRangeion between two images.
 The following datatype combinations are supported:
 *
 *  | Case    | Input   | Output  |
 *  |  ----:  | :----:  | :----   |
 *  |    1    | uint8_t | uint8_t |
 *  |    2    | int8_t  | int8_t  |
 *  |    3    | uint16_t| uint16_t|
 *  |    2    | int16_t | int16_t |

 * @par Method
 * @verbatim

    dst(x,y) = falseValue    if src(x,y) > upper
    dst(x,y) = falseValue    if src(x,y) < lower
    dst(x,y) = trueValue     otherwise

   @endverbatim
 *
 * OpenVX Function Reference Page :
 https://www.khronos.org/registry/vx/specs/1.1/html/d3/d1e/group__group__vision__function__threshold.html
 *
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
} VXLIB_thresholdRange_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */

int32_t VXLIB_thresholdRange_getHandleSize(VXLIB_thresholdRange_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_thresholdRange_exec function is called. This
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

VXLIB_STATUS VXLIB_thresholdRange_init(VXLIB_kernelHandle                   handle,
                                       VXLIB_bufParams2D_t                 *bufParamsIn,
                                       VXLIB_bufParams2D_t                 *bufParamsOut,
                                       const VXLIB_thresholdRange_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_thresholdRange_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_thresholdRange_init, and this function
 *               must be called before the
 *               @ref VXLIB_thresholdRange_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn :  Pointer to the structure containing dimensional
 *                               information of input image
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output buffer
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 *                               parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *
 *  @remarks     None
 */

VXLIB_STATUS
VXLIB_thresholdRange_init_checkParams(VXLIB_kernelHandle                   handle,
                                      const VXLIB_bufParams2D_t           *bufParamsIn,
                                      const VXLIB_bufParams2D_t           *bufParamsOut,
                                      const VXLIB_thresholdRange_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_thresholdRange_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_thresholdRange_exec, and this function
 *               must be called before the
 *               @ref VXLIB_thresholdRange_exec is called.
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn   :  Pointer to the structure input image
 *  @param [out] pOut   :  Pointer to the output buffer
 *  @param [in]  pUpperVal   :  Pointer to the upper value
 *  @param [in]  pLowerVal   :  Pointer to the lower value
 *  @param [in]  pTrueVal   :  Pointer to the true value
 *  @param [in]  pFalseVal   :  Pointer to the false value
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     None
 */

VXLIB_STATUS VXLIB_thresholdRange_exec_checkParams(VXLIB_kernelHandle handle,
                                                   const void *restrict pIn,
                                                   const void *restrict pOut,
                                                   const void *restrict pUpperVal,
                                                   const void *restrict pLowerVal,
                                                   const void *restrict pTrueVal,
                                                   const void *restrict pFalseVal);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_thresholdRange_exec
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn   :  Pointer to the structure input image
 *  @param [out] pOut   :  Pointer to the output image
 *  @param [in]  pUpperVal   :  Pointer to the upper value
 *  @param [in]  pLowerVal   :  Pointer to the lower value
 *  @param [in]  pTrueVal   :  Pointer to the true value
 *  @param [in]  pFalseVal   :  Pointer to the false value
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @par Assumptions:
 *    - None
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - The input and output data buffers are expected to be in L2 memory
 *    - The buffer pointers are assumed to be 64-byte aligned
 *
 *  @remarks     Before calling this function, application is expected to call
 *               @ref VXLIB_thresholdRange_init and
 *               @ref VXLIB_thresholdRange_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS VXLIB_thresholdRange_exec(VXLIB_kernelHandle handle,
                                       void *restrict pIn,
                                       void *restrict pOut,
                                       void *restrict pUpperVal,
                                       void *restrict pLowerVal,
                                       void *restrict pTrueVal,
                                       void *restrict pFalseVal);

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
void VXLIB_thresholdRange_perfEst(VXLIB_kernelHandle handle, size_t *archCycles, size_t *estCycles);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_ THRESHOLDRANGE_IXX_IXX_OXX_H_ */
