#include "stdafx.h"
#include "StartScene.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LPlayer.h"

CStartScene::CStartScene()
{
}


CStartScene::~CStartScene()
{
}

void CStartScene::Initialize()
{
	CObjMgr::Get_Inst()->Add_Obj(OBJ_PLAYER, CAbstractFactory<CLPlayer>::Create());
}

void CStartScene::Update()
{
	CObjMgr::Get_Inst()->Update();
}

void CStartScene::Late_Update()
{
	CObjMgr::Get_Inst()->Late_Update();
}

void CStartScene::Render(HDC hDC)
{
	CObjMgr::Get_Inst()->Render(hDC);
}

void CStartScene::Release()
{
}
