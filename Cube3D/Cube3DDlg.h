// Cube3DDlg.h
//

#pragma once

#include "OpenGL.h"
#include <vector>
using std::vector;

// CCube3DDlg
class CCube3DDlg : public CDialog
{
public:
    CCube3DDlg(CWnd* pParent = NULL);

    enum { IDD = IDD_CUBE3D_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL PreTranslateMessage(MSG* pMsg);


protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    virtual void OnOK() { return; }
    virtual void OnCancel() { return; }
    afx_msg void OnClose() { EndDialog(IDCANCEL); }

    DECLARE_MESSAGE_MAP()

private:
    /* selfrotate till NEW button clicked */
    bool selfRotate;
    /* if right button down */
    bool rButtonDown;
    /* point when right button down */
    CPoint rButtonPos;
    /* COpenGL */
    COpenGL opengl;
    /* current action index */
    size_t actIndex;
    /* rotation actions */
    vector <ACTION> actions;

public:
    void InitTimer();
    BOOL InitOpenGL();
    void AddAction(int face, bool clockwise, bool undo = false);
    void UpdateSteps(int face, bool clockwise);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnClickedButtonNew();
    afx_msg void OnClickedButtonShuffle();
    afx_msg void OnClickedButtonUndo();
    afx_msg void OnClickedButtonSolve();
};
