// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#ifndef VXLIB_TEST_C7XECR_H_
#define VXLIB_TEST_C7XECR_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void VXLIB_TEST_c7xSetTCR0(uint64_t param);

void VXLIB_TEST_c7xSetTBR0(uint64_t param);

void VXLIB_TEST_c7xSetMAR(uint64_t param);

void VXLIB_TEST_c7xSetSCR(uint64_t param);

// added during j721e bring-up to perform TLB invalidate ALL after the MMU setup
// code
void VXLIB_TEST_c7xMmuTlbInvAll(void);

void VXLIB_TEST_c7xSetL2CFG(uint64_t param);

uint64_t VXLIB_TEST_c7xGetL2CFG(void);

void VXLIB_TEST_c7xSetL1DCFG(uint64_t param);

uint64_t VXLIB_TEST_c7xGetL1DCFG(void);

#ifdef __cplusplus
}
#endif

#endif /* end of VXLIB_TEST_C7XECR_H_ definition */
