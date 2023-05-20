#include "stdafx.h"
#include "StartScene.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LPlayer.h"
#include	"LMonsterMgr.h"
#include	"LCollisionMgr.h"
#include	"TimeMgr.h"
#include	"LItemMgr.h"
#include	"LClock.h"
#include	<time.h>

CStartScene::CStartScene() : m_fGameTime(0.f)
{
}


CStartScene::~CStartScene()
{
	Release();
}

void CStartScene::Initialize()
{
	CObjMgr::Get_Inst()->Add_Obj(OBJ_PLAYER, CAbstractFactory<CLPlayer>::Create());

	CObj* clock = CAbstractFactory<CLClock>::Create();
	clock->Set_Pos({ WINCX*0.5f, 100, 0 });
	CObjMgr::Get_Inst()->Add_Obj(OBJ_UI, clock);
}

void CStartScene::Update()
{
	srand(unsigned((int)(GetTickCount() % (DWORD)32768)));

	CLMonsterMgr::Get_Inst()->Create_Monster();
	CLItemMgr::GetInst()->Create_Item();

	CObjMgr::Get_Inst()->Update();
}

void CStartScene::Late_Update()
{
	for (auto& iter : CObjMgr::Get_Inst()->Get_All(OBJ_PLAYER))
	{
		for (auto& iterB : CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER))
		{
			CLCollisionMgr::Collide(iter, iterB);
		}

		for (auto& iterB : CObjMgr::Get_Inst()->Get_All(OBJ_ITEM))
		{
			CLCollisionMgr::Collide(iter, iterB);
		}
	}

	if (!CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT).empty())
	{
		for (auto& iter : CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT))
		{
			for (auto& iterB : CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER))
			{
				CLCollisionMgr::Collide(iter, iterB);
			}
		}
	}



	CObjMgr::Get_Inst()->Late_Update();
}

void CStartScene::Render(HDC hDC)
{
	CObjMgr::Get_Inst()->Render(hDC);

}

void CStartScene::Release()
{
	CObjMgr::Get_Inst()->Clear_All();
}
