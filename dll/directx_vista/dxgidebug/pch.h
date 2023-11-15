/*
 * PROJECT:     ReactX Graphics Infrastructure Debug layer
 * COPYRIGHT:   See COPYING in the top level directory
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
