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
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CCube3DDlg::OnClickedButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_SHUFFLE, &CCube3DDlg::OnClickedButtonShuffle)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, &CCube3DDlg::OnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_SOLVE, &CCube3DDlg::OnClickedButtonSolve)
END_MESSAGE_MAP()


// CCube3DDlg

BOOL CCube3DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// init
	selfRotate = true;
	rButtonDown = false;
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

    CRect rect;
    GetDlgItem(IDC_DRAW)->GetClientRect(rect);
    GLsizei width = rect.right - rect.left;
    GLsizei height = rect.bottom - rect.top;

    opengl.init(width, height);

    return TRUE;
}

void CCube3DDlg::OnTimer(UINT_PTR nIDEvent)
{
    opengl.render(selfRotate);

    CDialog::OnTimer(nIDEvent);
}

BOOL CCube3DDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    CRect rect;
    GetDlgItem(IDC_DRAW)->GetWindowRect(rect);

    if (rect.PtInRect(pt))
    {
        opengl.zoomScene(zDelta);
    }

    return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CCube3DDlg::OnClickedButtonNew()
{
    selfRotate = false;
    GetDlgItem(IDC_BUTTON_SHUFFLE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_SOLVE)->EnableWindow(TRUE);

    opengl.resetScene();
}

void CCube3DDlg::OnClickedButtonShuffle()
{
    opengl.shuffleScene();
}

void CCube3DDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
    CRect rect;
    POINT pt = point;
    GetDlgItem(IDC_DRAW)->GetWindowRect(rect);
    ClientToScreen(&pt);

    if (rect.PtInRect(pt))
    {
        rButtonDown = true;
        rButtonPos = point;
    }
	
    CDialog::OnRButtonDown(nFlags, point);
}

void CCube3DDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
    if (rButtonDown)
    {
        rButtonDown = false;
    }

    CDialog::OnRButtonUp(nFlags, point);
}

void CCube3DDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect rect;
    POINT pt = point;
    GetDlgItem(IDC_DRAW)->GetWindowRect(rect);
    ClientToScreen(&pt);

    if (rect.PtInRect(pt) && rButtonDown)
    {
        opengl.setRot(point.x - rButtonPos.x, point.y - rButtonPos.y);
        rButtonPos = point;
    }
    else
    {
        rButtonDown = false;
    }

    CDialog::OnMouseMove(nFlags, point);
}

BOOL CCube3DDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_CHAR)
    {
        char key = pMsg->wParam;
        char act1[] = {'F', 'B', 'U', 'D', 'L', 'R'};
        char act2[] = {'f', 'b', 'u', 'd', 'l', 'r'};

        for (int i = 0; i < 6; i++)
        {
            if (key == act1[i])
            {
                opengl.setAction(i, true);
                break;
            }
            else if (key == act2[i])
            {
                opengl.setAction(i, false);
                break;
            }
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CCube3DDlg::OnClickedButtonUndo()
{

}

void CCube3DDlg::OnClickedButtonSolve()
{

}
