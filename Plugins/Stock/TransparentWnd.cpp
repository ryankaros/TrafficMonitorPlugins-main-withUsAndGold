#include "pch.h"
#include "TransparentWnd.h"
#include "FloatingWnd.h"
#include <Stock.h>

BEGIN_MESSAGE_MAP(CTransparentWnd, CWnd)
ON_WM_LBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_WM_CREATE()
END_MESSAGE_MAP()

int CTransparentWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    TRACE(L"CTransparentWnd Created\n");
    return 0;
}

CTransparentWnd::CTransparentWnd() : m_pParent(nullptr)
{
}

void CTransparentWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
    TRACE(L"CTransparentWnd OnLButtonDown\n");

    // Get cursor position
    CPoint ptScreen;
    GetCursorPos(&ptScreen);

    // Get floating window rect
    CRect rcFloat;
    if (m_pParent && m_pParent->GetSafeHwnd())
    {
        m_pParent->GetWindowRect(rcFloat);
        if (!rcFloat.PtInRect(ptScreen))
        {
            TRACE(L"Destroying floating window\n");
            DestroyWindow();
            Stock::Instance().DestroyFloatingWnd();
        }
        else
        {
            // Click inside floating window: forward message to it
            m_pParent->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
        }
    }
}

BOOL CTransparentWnd::OnEraseBkgnd(CDC *pDC)
{
    return TRUE; // do not erase background
}
