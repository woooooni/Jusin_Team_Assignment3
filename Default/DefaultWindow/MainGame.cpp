#include "stdafx.h"
#include "MainGame.h"
#include	"SceneMgr.h"
#include	"TimeMgr.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CSceneMgr::Get_Inst()->Initialize();
	CTimeMgr::GetInst()->Initialize();
}

void CMainGame::Update(void)
{
	CTimeMgr::GetInst()->Update();
	CSceneMgr::Get_Inst()->Update();

}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Inst()->Late_Update();

}

void CMainGame::Render()
{
	HDC memDC = CreateCompatibleDC(m_DC);
	HBITMAP memBitmap = CreateCompatibleBitmap(m_DC, WINCX, WINCY);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

	Rectangle(memDC, 0, 0, WINCX, WINCY);

	CSceneMgr::Get_Inst()->Render(memDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, memDC, 0, 0, SRCCOPY);

	SelectObject(memDC, oldBitmap);
	DeleteObject(memBitmap);
	DeleteDC(memDC);

}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Inst()->Release();

	ReleaseDC(g_hWnd, m_DC);
	
}

