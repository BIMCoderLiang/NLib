// SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

/**********************************************************************/
/* SmSmlibAll.h: Minimal SMLib compatibility shim                     */
/*                                                                    */
/* NLib's NURBS algorithms are self-contained and do NOT require the  */
/* full SMLib / B-Rep kernel. The symbols NLib references from        */
/* <SmSmlibAll.h> are defined below, so this header lets NLib build   */
/* standalone on Windows, Linux and macOS.                            */
/*                                                                    */
/* If you later want to link against real SMLib, remove this file and */
/* add the SMLib include directory to the target's include path.      */
/**********************************************************************/

#ifndef NMT_SMSMLIBALL_H
#define NMT_SMSMLIBALL_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
#  include <limits>   /* std::numeric_limits (used by NL_SrfNurb.cpp) */
#endif

/* Upper bound for formatted strings (used by N_PRINTF's sanity check). */
#ifndef SM_TBLOCK_SIZE
#define SM_TBLOCK_SIZE 2048
#endif

/* "Effective zero" tolerance for knot-parameter comparisons.          */
#ifndef SM_EFF_ZERO_PARAM
#define SM_EFF_ZERO_PARAM 1.0e-14
#endif

/* Assertion used by N_PRINTF and the debug helpers.                   */
#ifndef SM_ASSERT
#define SM_ASSERT(expr) assert(expr)
#endif

/* Boolean constants normally supplied by <windows.h> / SMLib.         */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif /* NMT_SMSMLIBALL_H */
