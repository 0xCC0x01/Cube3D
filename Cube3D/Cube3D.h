// Cube3D.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
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