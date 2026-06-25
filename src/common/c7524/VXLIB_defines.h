// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef C7524_VXLIB_DEFINES_H_
#define C7524_VXLIB_DEFINES_H_ 1

/*******************************************************************************
 *
 * SOC HARDWARE DEFINES
 *
 ******************************************************************************/

#if !defined(_HOST_BUILD)
// disable L2 aux buffer for host emulation for better valgrind results
#define VXLIB_L2_AUX_BUFFER 1
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* C7524_VXLIB_DEFINES_H_ */
