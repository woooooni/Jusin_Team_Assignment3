#include "stdafx.h"
#include "SceneMgr.h"

#include	"ObjMgr.h"
#include	"LIntroScene.h"
#include "Scene_Taewon.h"
#include	"JScene.h"
#include	"StartScene.h"


CSceneMgr* CSceneMgr::inst = nullptr;
CSceneMgr::CSceneMgr() 
	: m_pCurScene(nullptr)
	, m_eNextType(SCENE_END)
{

}


CSceneMgr::~CSceneMgr()
{

}

void CSceneMgr::Initialize()
{
	Safe_Delete(m_pCurScene);

	m_pCurScene = new CJScene;
	m_pCurScene->Initialize();
}

void CSceneMgr::Change_Scene(SCENE_TYPE p_Type)
{
	if (m_pCurScene->Get_SType() != p_Type)
	{
		switch (p_Type)
		{
		case SCENE_START:
			Safe_Delete(m_pCurScene);

			m_pCurScene = new CLIntroScene;
			m_pCurScene->Initialize();
			break;

		case	SCENE_L:
			
			Safe_Delete(m_pCurScene);

			m_pCurScene = new CStartScene;
			m_pCurScene->Initialize();


			break;

		case SCENE_TAWON:
			break;

		case SCENE_END:
			break;
		default:
			break;
		}
	}
}

