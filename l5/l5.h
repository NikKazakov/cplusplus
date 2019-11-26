
// l5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cl5App:
// See l5.cpp for the implementation of this class
//

class Cl5App : public CWinApp
{
public:
	Cl5App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cl5App theApp;
