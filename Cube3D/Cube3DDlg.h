// Cube3DDlg.h
//

#pragma once

#include "OpenGL.h"

// CCube3DDlg
class CCube3DDlg : public CDialog
{
public:
	CCube3DDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_CUBE3D_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	COpenGL opengl;

public:
	void InitTimer();
	BOOL InitOpenGL();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonNew();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
