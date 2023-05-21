#include "stdafx.h"
#include "MyBMP.h"
#include "Define.h"

CMyBMP::CMyBMP()
{
}


CMyBMP::~CMyBMP()
{
	Release();
}

void CMyBMP::Release()
{
	SelectObject(m_DC, m_bitOldMap);
	DeleteObject(m_bitNowMap);
	DeleteDC(m_DC);
}

void CMyBMP::Load_MyImage(const TCHAR * m_str)
{
	HDC tmp = GetDC(g_hWnd);
	m_DC = CreateCompatibleDC(tmp);
	ReleaseDC(g_hWnd, tmp);
	m_bitNowMap = (HBITMAP)LoadImage(NULL, m_str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_bitOldMap = (HBITMAP)SelectObject(m_DC, m_bitNowMap);

}