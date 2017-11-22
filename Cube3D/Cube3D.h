// Cube3D.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"


// CCube3DApp:
//

class CCube3DApp : public CWinApp
{
public:
	CCube3DApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CCube3DApp theApp;