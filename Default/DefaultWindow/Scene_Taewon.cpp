#include "stdafx.h"
#include "Scene_Taewon.h"
#include "ObjMgr.h"
#include "Player_TW.h"
#include "Ground_TW.h"
#include "CollisionMgr_TW.h"
#include "Camera_TW.h"
#include "Monster_TW.h"
#include "KeyMgr.h"
#include "SoundMgr.h"


CScene_Taewon::CScene_Taewon()
	:m_bGuide(true)
{
}


CScene_Taewon::~CScene_Taewon()
{
}

void CScene_Taewon::Initialize()
{
	CPlayer_TW* pPlayer = new CPlayer_TW;
	pPlayer->Initialize();
	pPlayer->SetPos(D3DXVECTOR3{ 10.f, -500.f, 0.f });
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
	pGround->SetScale(D3DXVECTOR3{ 300.f, 100.f, 0.f });
	pGround->Initialize();
	pGround->SetPos(D3DXVECTOR3{ 1600.f, WINCY - 400.f, 0.f });
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
	pMonster->SetSpecialDead(true);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_MONSTER].push_back(pMonster);

	pMonster = new CMonster_TW;
	pMonster->Initialize();
	pMonster->SetPos(D3DXVECTOR3{ 950.f, 0.f, 0.f });
	pMonster->SetTarget(pPlayer);
	pMonster->SetScene(this);
	pMonster->SetSpecialDead(false);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_MONSTER].push_back(pMonster);

	pMonster = new CMonster_TW;
	pMonster->Initialize();
	pMonster->SetPos(D3DXVECTOR3{ 1500.f, 0.f, 0.f });
	pMonster->SetTarget(pPlayer);
	pMonster->SetScene(this);
	pMonster->SetSpecialDead(false);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_MONSTER].push_back(pMonster);

	pMonster = new CMonster_TW;
	pMonster->Initialize();
	pMonster->SetPos(D3DXVECTOR3{ 1700.f, 0.f, 0.f });
	pMonster->SetTarget(pPlayer);
	pMonster->SetScene(this);
	pMonster->SetSpecialDead(false);
	m_arrVecObj[(UINT)OBJ_TYPE::OBJ_MONSTER].push_back(pMonster);


	CCamera_TW::GetInst()->Initialize();
	CCamera_TW::GetInst()->SetTargetObj(pPlayer);

	CSoundMgr::GetInst()->StopAll();
	CSoundMgr::GetInst()->PlayBGM(L"Bgm_KatanaZero.mp3", 1.f);
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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		m_bGuide = !m_bGuide;
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
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_MONSTER), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_GROUND), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_GROUND), false);

	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_LASER), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_LASER), GetObjVec(OBJ_TYPE::OBJ_BULLET), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_PLAYER), GetObjVec(OBJ_TYPE::OBJ_BULLET), false);
	CCollisionMgr_TW::GetInst()->Collision_RectEx(GetObjVec(OBJ_TYPE::OBJ_MONSTER), GetObjVec(OBJ_TYPE::OBJ_BULLET), false);
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
	SetBkMode(hDC, TRANSPARENT);

	if (m_bGuide)
	{
		wstring strHelp			= L"F1                : 도움말 켜기/끄기";
		wstring strMoveGuide	= L"A, D             : 이동";
		wstring strJumpGuide	= L"SPACE        : 점프";
		wstring strAttackGuide	= L"L_MOUSE   : 레이저";
		wstring strTimeRewind	= L"R                 : 시간 되돌리기";
		wstring strGhostModeGuide = L"F                 : 고스트 모드 On/Off";
		wstring strTimeSlow		= L"TAB             : 타임 슬립";

		TextOut(hDC, int(50.f), int(WINCY - 140.f), strHelp.c_str(), strHelp.size());
		TextOut(hDC, int(50.f), int(WINCY - 120.f), strMoveGuide.c_str(), strMoveGuide.size());
		TextOut(hDC, int(50.f), int(WINCY - 100.f), strJumpGuide.c_str(), strJumpGuide.size());
		TextOut(hDC, int(50.f), int(WINCY - 80.f), strAttackGuide.c_str(), strAttackGuide.size());
		TextOut(hDC, int(50.f), int(WINCY - 60.f), strTimeRewind.c_str(), strTimeRewind.size());
		TextOut(hDC, int(50.f), int(WINCY - 40.f), strGhostModeGuide.c_str(), strGhostModeGuide.size());
		TextOut(hDC, int(50.f), int(WINCY - 20.f), strTimeSlow.c_str(), strTimeSlow.size());
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
	CSoundMgr::GetInst()->StopSound(CHANNELID::SOUND_TIMEREWIND);
;	CSoundMgr::GetInst()->PlaySound(L"TimeRewind.wav", CHANNELID::SOUND_TIMEREWIND, 1.f);
}
