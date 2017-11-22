// Cube3D.cpp
//

#include "stdafx.h"
#include "Cube3D.h"
#include "Cube3DDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCube3DApp

BEGIN_MESSAGE_MAP(CCube3DApp, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCube3DApp

CCube3DApp::CCube3DApp()
{
	// TODO:
}


CCube3DApp theApp;


// CCube3DApp

BOOL CCube3DApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	SetRegistryKey(_T("0xCC"));

	CCube3DDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}
