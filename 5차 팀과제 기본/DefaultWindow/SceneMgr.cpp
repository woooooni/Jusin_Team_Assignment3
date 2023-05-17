#include "stdafx.h"
#include "SceneMgr.h"

#include	"ObjMgr.h"


CSceneMgr* CSceneMgr::inst = nullptr;

CSceneMgr::CSceneMgr() : m_pCurScene(nullptr), m_eNextType(SCENE_END)
{

}


CSceneMgr::~CSceneMgr()
{

}

void CSceneMgr::Change_Scene(SCENE_TYPE p_Type)
{
	if (m_pCurScene->Get_SType() != p_Type)
	{
		switch (p_Type)
		{
		case SCENE_START:

			break;

		case SCENE_END:
			break;
		default:
			break;
		}
	}
}

