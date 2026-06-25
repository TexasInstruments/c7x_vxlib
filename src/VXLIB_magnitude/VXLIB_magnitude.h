// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_MAGNITUDE_IXX_IXX_OXX_H_
#define VXLIB_MAGNITUDE_IXX_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_magnitude VXLIB_magnitude
 * @brief Kernel for adding two input vector data
 *
 *
 * @details
 *  This kernel takes two gradients in S16 format and computes the S16 normalized magnitude.
 *  The following datatype combinations are supported:
 *
 *  | Case    | Input0  | Input1  | Output  |
 *  |  ----:  | :----:  | :----:  | :----   |
 *  |    1    | int16_t | int16_t | int16_t |
 *
 * @par Method
 * The magnitude is computed using the following equation:
 * @verbatim

    dst(x,y) = sqrt(src0(x,y)^2+src1(x,y)^2)

   @endverbatim
 *
 * The square root internally calculated in single precision foloat. It then converted to the output datatype.
 * This might cause deviation from the expected output due to the rounding method used when converting to the output
 datatype.
 * This method is tested with tolerance of 1.
 * @ingroup  VXLIB
 */

/**@{*/

/**
 * @brief Structure containing the parameters to initialize the kernel
 */

typedef struct {
   /** @brief Variant of the function, refer to @ref VXLIB_FUNCTION_STYLE     */
   int8_t funcStyle;
} VXLIB_magnitude_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */

int32_t VXLIB_magnitude_getHandleSize(VXLIB_magnitude_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_magnitude_exec function is called. This
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

VXLIB_STATUS VXLIB_magnitude_init(VXLIB_kernelHandle              handle,
                                  VXLIB_bufParams2D_t            *bufParamsIn0,
                                  VXLIB_bufParams2D_t            *bufParamsIn1,
                                  VXLIB_bufParams2D_t            *bufParamsOut,
                                  const VXLIB_magnitude_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_magnitude_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_magnitude_init, and this function
 *               must be called before the
 *               @ref VXLIB_magnitude_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn0 :  Pointer to the structure containing dimensional
 *                               information of input image 0
 *  @param [in]  bufParamsIn1 :  Pointer to the structure containing dimensional
 *                               information of input image 1
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
VXLIB_magnitude_init_checkParams(VXLIB_kernelHandle              handle,
                                 const VXLIB_bufParams2D_t      *bufParamsIn0,
                                 const VXLIB_bufParams2D_t      *bufParamsIn1,
                                 const VXLIB_bufParams2D_t      *bufParamsOut,
                                 const VXLIB_magnitude_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_magnitude_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_magnitude_init, and this function
 *               must be called before the
 *               @ref VXLIB_magnitude_init is called.
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

VXLIB_STATUS VXLIB_magnitude_exec_checkParams(VXLIB_kernelHandle handle,
                                              const void *restrict pIn0,
                                              const void *restrict pIn1,
                                              const void *restrict pOut);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_magnitude_exec
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn0   :  Pointer to the structure input image 0
 *  @param [in]  pIn1   :  Pointer to the structure input image 1
 *  @param [out] pOut   :  Pointer to the output image
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
 *               @ref VXLIB_magnitude_init and
 *               @ref VXLIB_magnitude_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS
VXLIB_magnitude_exec(VXLIB_kernelHandle handle, void *restrict pIn0, void *restrict pIn1, void *restrict pOut);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_MAGNITUDE_IXX_IXX_OXX_H_ */
