#include "stdafx.h"
#include "JScene.h"
#include "JPlayer.h"
#include "JBall.h"
#include "JItem_Ball.h"
#include "JItem_Bar.h"
#include "ObjMgr.h"
#include "JTileMgr.h"
#include "AbstractFactory.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "JCollisionMgr.h"

CJScene::CJScene()
	: m_iDrawTile(0), m_bGameOver(false), m_bGameStart(false), m_iCount(3)
{
	m_dwTime = GetTickCount();
}


CJScene::~CJScene()
{
	Release();
}

void CJScene::Initialize()
{
	CObjMgr::Get_Inst()->Add_Obj(OBJ_PLAYER, CAbstractFactory<CJPlayer>::Create());
	CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create());

	//CJTileMgr::Get_Instance()->Initialize();
	CJTileMgr::Get_Instance()->Load_Tile();
}

void CJScene::Update()
{
	srand(size_t(time(NULL)));

	CObjMgr::Get_Inst()->Update();
	CJTileMgr::Get_Instance()->Update();


	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos + VECTOR{ 0.f, -30.f, 0.f }));
	}

	//if (CKeyMgr::Get_Instance()->Key_Down('S'))
	//{
	//	CJTileMgr::Get_Instance()->Save_Tile();
	//}
	//if (CKeyMgr::Get_Instance()->Key_Down('1'))
	//{
	//	m_iDrawTile = 1;
	//}
	//else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	//{
	//	m_iDrawTile = 2;
	//}

	//if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	//{
	//	POINT pt{};
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	if (m_iDrawTile == 1)
	//	{
	//		CJTileMgr::Get_Instance()->Picking_Tile(pt, 1, 0);
	//	}
	//	else if (m_iDrawTile == 2)
	//	{
	//		CJTileMgr::Get_Instance()->Picking_Tile(pt, 2, 0);
	//	}
	//	
	//}
	//else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RBUTTON))
	//{
	//	POINT pt{};
	//	GetCursorPos(&pt);
	//	ScreenToClient(g_hWnd, &pt);

	//	CJTileMgr::Get_Instance()->Picking_Tile(pt, 0, 0);
	//}
}

void CJScene::Late_Update()
{
	if (!m_bGameStart)
	{
		if (m_dwTime + (100000.f * DELTA_TIME) <= GetTickCount())
		{
			--m_iCount;
			m_dwTime = GetTickCount();
		}
		if (m_iCount <= -1)
			m_bGameStart = true;

		return;
	}
		
	CJCollisionMgr::Collision_Rect(CObjMgr::Get_Inst()->Get_All(OBJ_PLAYER), CObjMgr::Get_Inst()->Get_All(OBJ_ITEM));
	CJCollisionMgr::Collision_Rect(CObjMgr::Get_Inst()->Get_All(OBJ_PLAYER), CObjMgr::Get_Inst()->Get_All(OBJ_BALL));

	CObjMgr::Get_Inst()->Late_Update();
	CJTileMgr::Get_Instance()->Late_Update();

	

	GameOver();
	GameClear();
}

void CJScene::Render(HDC hDC)
{
	CJTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Inst()->Render(hDC);
	

	if (m_iCount > 0 && !m_bGameStart)
	{
		swprintf_s(m_szCount, L"%d", m_iCount);
			
		hTitleFont = CreateFont(300, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, TEXT("Arial"));
		hOldFont = (HFONT)SelectObject(hDC, hTitleFont);
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 330, 150, m_szCount, lstrlen(m_szCount));
		SelectObject(hDC, hOldFont);
		DeleteObject(hTitleFont);
	}
	else if (m_iCount <= 0 && !m_bGameStart)
	{
		swprintf_s(m_szCount, L"Game Start");

		hTitleFont = CreateFont(150, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, TEXT("Arial"));
		hOldFont = (HFONT)SelectObject(hDC, hTitleFont);
		SetTextColor(hDC, RGB(0, 0, 0));
		SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, 50, 200, m_szCount, lstrlen(m_szCount));
		SelectObject(hDC, hOldFont);
		DeleteObject(hTitleFont);
	}
}

void CJScene::Release()
{
	CObjMgr::Get_Inst()->Clear_All();
	CJTileMgr::Get_Instance()->Release();
	CJTileMgr::Get_Instance()->Destroy_Instance();
}

void CJScene::GameOver()
{
	if (!m_bGameOver && CObjMgr::Get_Inst()->Get_All(OBJ_BALL).empty())
	{
		m_bGameOver = true;
		m_dwTime = GetTickCount();
		m_iCount = 3;
	}
	else if (m_bGameOver)
	{
		if (m_dwTime + (50000.f * DELTA_TIME) <= GetTickCount())
		{
			--m_iCount;
			m_dwTime = GetTickCount();
		}
		if (m_iCount < 0)
		{
			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos + (VECTOR(0.f, -1.f, 0.f) * 30.f)));
			m_bGameOver = false;
		}	
	}
}

void CJScene::GameClear()
{
	int iTileCount = 0;

	for (auto& iter : CJTileMgr::Get_Instance()->Get_vecTile())
	{
		if (1 == static_cast<CJTile*>(iter)->Get_DrawID())
			iTileCount++;
	}
	/*if (iTileCount <= 10)
		CSceneMgr::Get_Inst()->Change_Scene();*/
}
