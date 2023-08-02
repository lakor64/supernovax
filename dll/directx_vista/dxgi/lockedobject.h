/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     ???
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

class CLockedObject
{
public:
	virtual STDMETHODIMP_(void) TakeLock() {}
	virtual STDMETHODIMP_(void) ReleaseLock() {}
};

class CLockedObjectChild
{
public:
	virtual STDMETHODIMP_(void) TakeLock() {}
	virtual STDMETHODIMP_(void) ReleaseLock() {}
};
