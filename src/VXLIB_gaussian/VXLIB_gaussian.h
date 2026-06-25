// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_GAUSSIAN_IXX_IXX_OXX_H_
#define VXLIB_GAUSSIAN_IXX_IXX_OXX_H_

#include "../common/VXLIB_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup VXLIB_KERNELS
 */

/**
 * @defgroup VXLIB_gaussian VXLIB_gaussian
 * @brief Kernel for applying kxk gaussian filter on input image.
 *
 *
 * @details
 *  Performs a k x k gaussian filter on an input image.
 *  Filter size k is configured by passing accepted filter dimension through init args.
 *  Similarly, padded configuration can be set via init args (Padding = 0 supported only
 *  for now). For non-padded implementation, user must input image dimensions greater than or
 *  equal filter size.
 *  Currently, 3x3 filter size is supported and the following datatype combinations are
 *  supported by this function:
 *
 *  | Case    | Input   | Output  |
 *  |  ----:  | :----:  | :----:  |
 *  |    0    | uint8_t | uint8_t |
 *
 * @par Method
 * @verbatim

    3x3 gaussian filter: dst(x,y) = 1*(src(x+0,y+0) + 2*src(x+1,y+0) + 1*src(x+2,y+0) +
                               2*src(x+0,y+1) + 4*src(x+1,y+1) + 2*src(x+2,y+1) +
                               1*src(x+0,y+2) + 2*src(x+1,y+2) + 1*src(x+2,y+2)) / 16

    5x5 gaussian filter: dst(x,y) = (src(x+0,y+0) + 4*src(x+1,y+0) + 6*src(x+2,y+0) + 4*src(x+3,y+0) + src(x+4, y+0) +
                               4*src(x+0,y+1) + 16*src(x+1,y+1) + 24*src(x+2,y+1) + 16*src(x+3,y+1) + 4*src(x+4,y+1) +
                               6*src(x+0,y+2) + 24*src(x+1,y+2) + 36*src(x+2,y+2) + 24*src(x+3,y+2) + 6*src(x+4,y+2) +
                               4*src(x+0,y+3) + 16*src(x+1,y+3) + 24*src(x+2,y+3) + 16*src(x+3,y+3) + 4*src(x+4,y+3) +
                               src(x+0,y+4) + 4*src(x+1,y+4) + 6*src(x+2,y+4) + 4*src(x+3,y+4) + src(x+4,y+4)) >> shift

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

   /** @brief Width and height of filter     */
   int8_t filterSize;

   /** @brief Shift parameter for 5x5 filter     */
   uint8_t shift;

   /** @brief Padding options     */
   int32_t padLeft;
   int32_t padRight;
   int32_t padTop;
   int32_t padBottom;

} VXLIB_gaussian_InitArgs;

/**
 *  @brief        This is a query function to calculate the size of internal
 *                handle
 *  @param [in]   pKerInitArgs  : Pointer to structure holding init parameters
 *  @return       Size of the buffer in bytes
 *  @remarks      Application is expected to allocate buffer of the requested
 *                size and provide it as input to other functions requiring it.
 */

int32_t VXLIB_gaussian_getHandleSize(VXLIB_gaussian_InitArgs *pKerInitArgs);

/**
 *  @brief       This function should be called before the
 *               @ref VXLIB_gaussian_exec function is called. This
 *               function takes care of any one-time operations such as setting
 * up the configuration of required hardware resources such as the streaming engine.  The results of these
 *               operations are stored in the handle.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
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

VXLIB_STATUS VXLIB_gaussian_init(VXLIB_kernelHandle             handle,
                                 VXLIB_bufParams2D_t           *bufParamsIn,
                                 VXLIB_bufParams2D_t           *bufParamsOut,
                                 const VXLIB_gaussian_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_gaussian_init function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_gaussian_init, and this function
 *               must be called before the
 *               @ref VXLIB_gaussian_init is called.
 *
 *  @param [in]  handle       :  Active handle to the kernel
 *  @param [in]  bufParamsIn  :  Pointer to the structure containing dimensional
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
VXLIB_gaussian_init_checkParams(VXLIB_kernelHandle             handle,
                                const VXLIB_bufParams2D_t     *bufParamsIn,
                                const VXLIB_bufParams2D_t     *bufParamsOut,
                                const VXLIB_gaussian_InitArgs *pKerInitArgs);

/**
 *  @brief       This function checks the validity of the parameters passed to
 *               @ref VXLIB_gaussian_exec function. This function
 *               is called with the same parameters as the
 *               @ref VXLIB_gaussian_init, and this function
 *               must be called before the
 *               @ref VXLIB_gaussian_init is called.
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn    :  Pointer to the structure input image
 *  @param [out] pOut   :  Pointer to the output image
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @remarks     None
 */

VXLIB_STATUS
VXLIB_gaussian_exec_checkParams(VXLIB_kernelHandle handle, const void *restrict pIn, const void *restrict pOut);

/**
 *  @brief       This function is the main kernel compute function.
 *
 *  @details     Please refer to details under
 *               @ref VXLIB_gaussian_exec
 *
 *  @param [in]  handle :  Active handle to the kernel
 *  @param [in]  pIn    :  Pointer to the structure input image
 *  @param [out] pOut   :  Pointer to the output image
 *
 *  @return      Status value indicating success or failure. Refer to @ref VXLIB_STATUS.
 *
 *  @par Assumptions:
 *    - None
 *
 *  @par Performance Considerations:
 *    For best performance,
 *    - the input and output data image are expected to be in L2 memory
 *    - the buffer pointers are assumed to be 64-byte aligned
 *
 *  @remarks     Before calling this function, application is expected to call
 *               @ref VXLIB_gaussian_init and
 *               @ref VXLIB_gaussian_exec_checkParams functions.
 *               This ensures resource configuration and error checks are done
 * only once for several invocations of this function.
 */

VXLIB_STATUS
VXLIB_gaussian_exec(VXLIB_kernelHandle handle, void *restrict pIn, void *restrict pOut);

void VXLIB_gaussian_perfEst(VXLIB_kernelHandle handle, size_t *archCycles, size_t *estCycles);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* VXLIB_GAUSSIAN_IXX_IXX_OXX_H_ */
