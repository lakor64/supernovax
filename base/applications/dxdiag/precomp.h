/*
 * PROJECT:     SupernovaX Diagnostic Tool
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */
#ifndef PRECOMP_H__
#define PRECOMP_H__

#define WIN32_LEAN_AND_MEAN
#define COBJMACROS

#ifdef __PFF__
typedef struct IDxDiagContainer IDxDiagContainer; // fix declaration for xp
#define DECLSPEC_EXPORT __declspec(dllimport)
#endif

#include <stdarg.h>
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <dxdiag.h>

#include "resource.h"
#include "wine/debug.h"
#include "dxdiag_private.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(A) (sizeof(A)/sizeof(*(A)))
#endif

#include <dxdiagternl.h>

/* globals */
extern HINSTANCE hInstance;

#endif /* PRECOMP_H__ */
