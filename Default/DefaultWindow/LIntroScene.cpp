#include "stdafx.h"
#include "LIntroScene.h"
#include	"SceneMgr.h"
#include	"AbstractFactory.h"
#include	"ObjMgr.h"
#include	"LMyButton.h"


CLIntroScene::CLIntroScene()
{
}


CLIntroScene::~CLIntroScene()
{
	Release();
}

void CLIntroScene::Initialize()
{
	CObj*		startBut = CAbstractFactory<CLMyButton>::Create({ { WINCX * 0.5f, WINCY * 0.5f + 50.f , 0 }, {}, { 200.f, 50.f, 0 } });
	startBut->Set_Name(L"게임 시작");
	static_cast<CLMyButton*>(startBut)->Set_ClickEvent([]()
	{
		CSceneMgr::Get_Inst()->Change_Scene(SCENE_L);
	});

	CObjMgr::Get_Inst()->Add_Obj(OBJ_UI, startBut);

	startBut = CAbstractFactory<CLMyButton>::Create({ { WINCX * 0.5f, WINCY * 0.5f + 200.f , 0 },{},{ 200.f, 50.f, 0 } });
	startBut->Set_Name(L"다음 게임으로");
	static_cast<CLMyButton*>(startBut)->Set_ClickEvent([]()
	{
		CSceneMgr::Get_Inst()->Change_Scene(SCENE_JUN);
	});

	CObjMgr::Get_Inst()->Add_Obj(OBJ_UI, startBut);

}

void CLIntroScene::Update()
{
	CObjMgr::Get_Inst()->Update();
}

void CLIntroScene::Late_Update()
{
	CObjMgr::Get_Inst()->Late_Update();

}

void CLIntroScene::Render(HDC hDC)
{
	CObjMgr::Get_Inst()->Render(hDC);

}

void CLIntroScene::Release()
{
	CObjMgr::Get_Inst()->Clear_All();
}
