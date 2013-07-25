// 360tray.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy360trayApp:
// See 360tray.cpp for the implementation of this class
//

class CMy360trayApp : public CWinApp
{
public:
	CMy360trayApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy360trayApp theApp;