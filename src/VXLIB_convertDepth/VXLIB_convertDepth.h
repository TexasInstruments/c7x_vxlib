// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_CONVERTDEPTH_IXX_IXX_OXX_H_
#define VXLIB_CONVERTDEPTH_IXX_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_convertDepth VXLIB_convertDepth
 * @brief Kernel for converting bit depth of images from 16-bit to 8-bit and 8-bit to 16-bit
 *
 *
 * @details
 *  Performs bit depth conversion on an image.
 *  For conversion from 16-bit to 8-bit, the overflow handling is controlled by an overflow-policy parameter @ref
 VXLIB_OVERFLOW_POLICY.
 *  Use @ref VXLIB_WRAP as the parameter for wrap and @ref VXLIB_SATURATE for saturate
 *  The following datatype combinations are supported:
 *
 *  | Case    | Input0  | Output  |
 *  |  ----:  | :----:  | :----   |
 *  |    0    | uint8_t | int16_t |
 *  |    1    | int16_t | uint8_t |
 *
 *
 * @par Method
 * For 8-bit to 16-bit bit depth conversion:
 * @verbatim

    dst(x,y) = ((int16)src(x,y)) << shift;

   @endverbatim
 *
 * @par
 * For 16-bit to 8-bit bit depth conversion:
 * @verbatim

    For Wrap Policy:
    dst(x,y) = ((uint8)(src(x,y) >> shift));

    For Saturate Policy:
    int16 value = src(x,y) >> shift;
    value = value < 0 ? 0 : value;
    value = value > 255 ? 255 : value;
    dst(x,y) = (uint8)value;

   @endverbatim
 *
 * @ingroup  VXLIB
 */

/**@{*/

/**
 * @brief Structure containing the parameters to initialize the kernel
 */
typedef struct {
   /** @brief Variant of the function refer to @ref VXLIB_FUNCTION_STYLE     */
   int8_t funcStyle;
   /** @brief Size of input data                                              */
   uint32_t dataSize;
   /** @brief Shift parameter  */
   uint8_t shift;
   /** @brief Overflow policy, refer to @ref VXLIB_OVERFLOW_POLICY   */
   VXLIB_OVERFLOW_POLICY overFlowPolicy;
} VXLIB_convertDepth_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */
int32_t VXLIB_convertDepth_getHandleSize(VXLIB_convertDepth_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_convertDepth_exec function is called. This
 *               function takes care of any one-time operations such as setting
 * up the configuration of required hardware resources such as the MMA
 *               accelerator and the streaming engine.  The results of these
 *               operations are stored in the handle.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn0  :  Pointer to the structure containing dimensional
 *                               information of input image
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output image
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 * parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 *  @remarks     Application is expected to provide a valid handle.
 */
VXLIB_STATUS VXLIB_convertDepth_init(VXLIB_kernelHandle                 handle,
                                     VXLIB_bufParams2D_t               *bufParamsIn0,
                                     VXLIB_bufParams2D_t               *bufParamsOut,
                                     const VXLIB_convertDepth_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_convertDepth_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_convertDepth_init, and this function
 *               must be called before the
 *               @ref VXLIB_convertDepth_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn0  :  Pointer to the structure containing dimensional
 *                               information of input image
 *  @param [out] bufParamsOut :  Pointer to the structure containing dimensional
 *                               information of output image
 *  @param [in]  pKerInitArgs :  Pointer to the structure holding init
 * parameters
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 *  @remarks     None
 */
VXLIB_STATUS
VXLIB_convertDepth_init_checkParams(VXLIB_kernelHandle                 handle,
                                    const VXLIB_bufParams2D_t         *bufParamsIn0,
                                    const VXLIB_bufParams2D_t         *bufParamsOut,
                                    const VXLIB_convertDepth_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_convertDepth_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_convertDepth_init, and this function
 *               must be called before the
 *               @ref VXLIB_convertDepth_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  pIn0  :  Pointer to the structure input image
 *  @param [out] pOut :  Pointer to the output buffer
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 *  @remarks     None
 */
VXLIB_STATUS
VXLIB_convertDepth_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn0, const void *restrict pOut);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_convertDepth_exec
 *
 *  @param [in]  handle      : Active handle to the kernel
 *  @param [in]  pIn0         : Pointer to buffer holding the input image
 *  @param [out] pOut        : Pointer to buffer holding the output image
 *
 *  @return      Status value indicating success or failure. Refer to @ref
 * VXLIB_STATUS.
 *
 *  @par Assumptions:
 *    - None
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data images are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 *  @remarks     Before calling this function, application is expected to call
 *               @ref VXLIB_convertDepth_init and
 *               @ref VXLIB_convertDepth_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS
VXLIB_convertDepth_exec(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pOut);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_CONVERTDEPTH_IXX_IXX_OXX_H_ */
