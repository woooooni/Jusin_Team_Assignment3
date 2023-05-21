#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
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

	HBITMAP old = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(old);

	CSoundMgr::GetInst()->Initialize();
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
	Rectangle(m_memDC, 0, 0, WINCX, WINCY);
	CSceneMgr::Get_Inst()->Render(m_memDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);
}

void CMainGame::Release(void)
{
	
	
	CKeyMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Inst()->Release();
	CObjMgr::Get_Inst()->Destroy_Inst();
	

	ReleaseDC(g_hWnd, m_memDC);
	ReleaseDC(g_hWnd, m_hDC);
}

