// Cube3D.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
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