// SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: Apache-2.0

/**********************************************************************
* FILE NAME --- StdAfx.h
* PURPOSE --- Precompiled Headers.
*
* NLib's NURBS algorithms are self-contained and do NOT require the
* full SMLib / B-Rep kernel. This header previously included SMLib's
* <SmSmlibAll.h>; the few symbols NLib actually needed from it are now
* defined directly below, so the library builds standalone on Windows,
* Linux and macOS.
**********************************************************************/

#ifndef NMT_STDAFX_H
#define NMT_STDAFX_H

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

/* "Effective zero" tolerance for knot-parameter comparisons. */
#ifndef SM_EFF_ZERO_PARAM
#define SM_EFF_ZERO_PARAM 1.0e-14
#endif

/* Assertion used by N_PRINTF and the debug helpers. */
#ifndef SM_ASSERT
#define SM_ASSERT(expr) assert(expr)
#endif

/* Boolean constants normally supplied by <windows.h> / SMLib. */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif // NMT_STDAFX_H
