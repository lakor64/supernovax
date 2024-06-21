/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * LICENSE:     LGPL-2.0-or-later (https://spdx.org/licenses/LGPL-2.0-or-later.html)
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
 
#pragma once

#include <dxgishared.h>

// definition fix for dxgidebug
#ifdef GetMessage
#undef GetMessage
#endif

#include <dxgidebug.h>
