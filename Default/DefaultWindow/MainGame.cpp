#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "TimeMgr.h"

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
	m_hDC = GetDC(g_hWnd);

	m_hBit = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	m_memDC = CreateCompatibleDC(m_hDC);


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

	Rectangle(memDC, 0, 0, WINCX, WINCY);

	CSceneMgr::Get_Inst()->Render(memDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, memDC, 0, 0, SRCCOPY);


}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Inst()->Release();

	ReleaseDC(g_hWnd, m_memDC);
	ReleaseDC(g_hWnd, m_hDC);
}

