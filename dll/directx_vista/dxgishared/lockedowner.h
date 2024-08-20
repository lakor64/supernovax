/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Simple wrapper of a mutex
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#pragma once

#include <lockowner.h>

class ATL_NO_VTABLE CLockedOwner
	: public ILockOwner
{
public:
	CLockedOwner()
	{
		InitializeCriticalSection(&m_loCs);
	}

	~CLockedOwner()
	{
		DeleteCriticalSection(&m_loCs);
	}

	STDMETHODIMP_(void) LOEnter(void) override
	{
		EnterCriticalSection(&m_loCs);
	}

	STDMETHODIMP_(void) LOLeave(void) override
	{
		LeaveCriticalSection(&m_loCs);
	}

	STDMETHODIMP_(BOOL) LOTryEnter(void) override
	{
		return TryEnterCriticalSection(&m_loCs);
	}

private:
	CRITICAL_SECTION m_loCs;
};
