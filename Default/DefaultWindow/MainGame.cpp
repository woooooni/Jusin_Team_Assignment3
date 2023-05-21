#include "stdafx.h"
#include "MainGame.h"
#include	"SceneMgr.h"
#include	"TimeMgr.h"
#include	"BmpMgr.h"

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
	CBmpMgr::GetInst()->Insert_Image(L"../Image/Background.bmp", L"BackBuff");

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
	HDC		img1 = CBmpMgr::GetInst()->Get_Image(L"BackBuff");


	BitBlt(m_DC, 0, 0, WINCX, WINCY, img1, 0, 0, SRCCOPY);




	Rectangle(img1, 0, 0, WINCX, WINCY);
	CTimeMgr::GetInst()->Render();

	CSceneMgr::Get_Inst()->Render(img1);






}

void CMainGame::Release(void)
{
	CSceneMgr::Get_Inst()->Release();

	ReleaseDC(g_hWnd, m_DC);
	
}

