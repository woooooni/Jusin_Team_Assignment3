#include "stdafx.h"
#include "MainGame.h"
#include	"SceneMgr.h"

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
}

void CMainGame::Update(void)
{
	CSceneMgr::Get_Inst()->Update();

}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Inst()->Late_Update();

}

void CMainGame::Render()
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	CSceneMgr::Get_Inst()->Render(m_DC);


}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Inst()->Release();

	ReleaseDC(g_hWnd, m_DC);
	
}

