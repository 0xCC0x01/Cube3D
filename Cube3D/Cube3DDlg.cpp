// Cube3DDlg.cpp
//

#include "stdafx.h"
#include "Cube3D.h"
#include "Cube3DDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define OPENGL_RENDER_TIMER    (1)

// CCube3DDlg


CCube3DDlg::CCube3DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCube3DDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCube3DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCube3DDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CCube3DDlg::OnClickedButtonNew)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CCube3DDlg

BOOL CCube3DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO:
	InitOpenGL();
	InitTimer();

	return TRUE;
}

void CCube3DDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCube3DDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCube3DDlg::InitTimer()
{
    SetTimer(OPENGL_RENDER_TIMER, 12, NULL);
}

BOOL CCube3DDlg::InitOpenGL()
{
    CDC *dc = new CClientDC(GetDlgItem(IDC_DRAW));
    opengl.setupPixelFormat(dc);
    HGLRC rc = wglCreateContext(dc->GetSafeHdc());
    wglMakeCurrent(dc->GetSafeHdc(), rc);

    CRect rect;
    GetDlgItem(IDC_DRAW)->GetClientRect(rect);
    GLsizei width = rect.right - rect.left;
    GLsizei height = rect.bottom - rect.top;

    opengl.init(width, height);

    return TRUE;
}

void CCube3DDlg::OnTimer(UINT_PTR nIDEvent)
{
    opengl.renderScene();

    CDialog::OnTimer(nIDEvent);
}

void CCube3DDlg::OnClickedButtonNew()
{
    KillTimer(OPENGL_RENDER_TIMER);
    GetDlgItem(IDC_BUTTON_SHUFFLE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_RESTORE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SOLVE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_ACTION)->EnableWindow(TRUE);

    opengl.resetScene();
}

BOOL CCube3DDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    opengl.zoomScene(zDelta);

    return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
