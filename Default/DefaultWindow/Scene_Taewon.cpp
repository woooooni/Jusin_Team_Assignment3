#include "stdafx.h"
#include "Scene_Taewon.h"
#include "ObjMgr.h"
#include "Player_TW.h"
#include "Ground_TW.h"
#include "CollisionMgr_TW.h"
#include "Camera_TW.h"
#include "Monster_TW.h"


CScene_Taewon::CScene_Taewon()
{
}


CScene_Taewon::~CScene_Taewon()
{
}

void CScene_Taewon::Initialize()
{
	CPlayer_TW* pPlayer = new CPlayer_TW;
	pPlayer->Initialize();
	pPlayer->SetPos(D3DXVECTOR3{ 10.f, 20.f, 0.f });
	pPlayer->SetScene(this);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_PLAYER].push_back(pPlayer);
	
	CObj_TW* pGround = new CGround_TW;
	pGround->SetScale(D3DXVECTOR3{ 100.f, 300.f, 0.f });
	pGround->Initialize();
	pGround->SetPos(D3DXVECTOR3{ 1000.f, WINCY - 310.f, 0.f });
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_GROUND].push_back(pGround);


	pGround = new CGround_TW;
	pGround->SetScale(D3DXVECTOR3{ 100.f, 300.f, 0.f });
	pGround->Initialize();
	pGround->SetPos(D3DXVECTOR3{ 1000.f, WINCY - 310.f, 0.f });
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_GROUND].push_back(pGround);

	pGround = new CGround_TW;
	pGround->SetScale(D3DXVECTOR3{ 100.f, 300.f, 0.f });
	pGround->Initialize();
	pGround->SetPos(D3DXVECTOR3{ 700.f, WINCY - 400.f, 0.f });
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_GROUND].push_back(pGround);

	pGround = new CGround_TW;
	pGround->SetScale(D3DXVECTOR3{ 100000.f, 300.f, 0.f });
	pGround->Initialize();
	pGround->SetPos(D3DXVECTOR3{ WINCX / 2.f, WINCY - 20.f, 0.f });
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_GROUND].push_back(pGround);

	CMonster_TW* pMonster = new CMonster_TW;
	pMonster->Initialize();
	pMonster->SetPos(D3DXVECTOR3{ 1050.f, WINCY - 310.f, 0.f });
	pMonster->SetTarget(pPlayer);
	pMonster->SetScene(this);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_MONSTER].push_back(pMonster);

	CCamera_TW::GetInst()->Initialize();
	CCamera_TW::GetInst()->SetLookAt({ 1.f, 1.f, 0.f }, false);
	CCamera_TW::GetInst()->SetTargetObj(pPlayer);
}

void CScene_Taewon::Update()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::OBJ_END; ++i)
	{
		for (UINT j = 0; j < m_arrVecObj[i].size(); ++j)
		{
			m_arrVecObj[i][j]->Update();
		}
	}
}

void CScene_Taewon::Late_Update()
{
	CCamera_TW::GetInst()->Update();
	for (UINT i = 0; i < (UINT)OBJ_TYPE::OBJ_END; ++i)
	{
		for (UINT j = 0; j < m_arrVecObj[i].size(); ++j)
		{
			m_arrVecObj[i][j]->Late_Update();
		}
	}
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_MONSTER), true);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_GROUND), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_GROUND), false);

	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_LASER), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER_BULLET), GetObjVec(OBJ_TYPE::OBJ_LASER), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_MONSTER_BULLET), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_PLAYER_BULLET), false);
}

void CScene_Taewon::Render(HDC hDC)
{
	CCamera_TW::GetInst()->Render(hDC);

	for (UINT i = 0; i < (UINT)OBJ_TYPE::OBJ_END; ++i)
	{
		vector<CObj_TW*>::iterator iter = m_arrVecObj[i].begin();
		for (; iter != m_arrVecObj[i].end();)
		{
			if ((*iter)->IsDelete())
			{
				Safe_Delete<CObj_TW*>((*iter));
				iter = m_arrVecObj[i].erase(iter);
				continue;
			}
			else
			{
				if ((*iter)->IsActive())
					(*iter)->Render(hDC);
				++iter;
			}
		}
	}

	
}

void CScene_Taewon::Release()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::OBJ_END; ++i)
	{
		for (UINT j = 0; j < m_arrVecObj[i].size(); ++j)
		{
			Safe_Delete<CObj_TW*>(m_arrVecObj[i][j]);
		}
	}
}

void CScene_Taewon::AddObj(CObj_TW * _pObj)
{
	m_arrVecObj[(UINT)_pObj->GetObjType()].push_back(_pObj);
}

void CScene_Taewon::TimeRewind()
{
	for (UINT i = 0; i < (UINT)OBJ_TYPE::OBJ_END; ++i)
	{
		for (UINT j = 0; j < m_arrVecObj[i].size(); ++j)
		{
			m_arrVecObj[i][j]->ChangeState(STATE::TIME_REWIND);
		}
	}
}
