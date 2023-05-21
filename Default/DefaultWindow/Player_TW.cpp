#include "stdafx.h"
#include "Player_TW.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Camera_TW.h"
#include "Laser_TW.h"
#include "SceneMgr.h"
#include "Ground_TW.h"
#include "Ghost_TW.h"
#include "Scene_Taewon.h"

CPlayer_TW::CPlayer_TW()
	: CObj_TW(OBJ_TYPE::OBJ_PLAYER)
	, m_fForceY(980.f)
	, m_pScene(nullptr)
	, m_pGround(nullptr)
	, m_pGhost(nullptr)
{

}


CPlayer_TW::~CPlayer_TW()
{

}


void CPlayer_TW::Initialize(void)
{
	m_fSpeed = 300.f;

	SetScale(D3DXVECTOR3{ 30.f, 30.f, 0.f });

	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });

	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
		m_vecVertices.push_back(m_vecOriginVertices[i]);

	ChangeState(STATE::JUMP);

	m_pGhost = new CGhost_TW;
	m_pGhost->SetScale(D3DXVECTOR3{ 30.f, 30.f, 0.f });
	m_pGhost->Initialize();
}

int CPlayer_TW::Update(void)
{
	if (m_pGround == nullptr)
		SetGround(false);
	switch (m_eState)
	{
	case STATE::IDLE:
		Update_Idle();
		break;
	case STATE::MOVE:
		Update_Move();
		break;
	case STATE::HANG:
		Update_Hang();
		break;
	case STATE::JUMP:
		Update_Jump();
		break;
	case STATE::TIME_REWIND:
		Update_TimeRewind();
		break;
	case STATE::DIE:
		Update_Die();
		break;
	}

	ResetVertices();

	D3DXMATRIX matScale, matRotZ, matTrans;

	float fMagnification = CCamera_TW::GetInst()->GetMagnification();
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	if (m_eState != STATE::TIME_REWIND)
	{
		Update_TimeStamp();
		m_pGround = nullptr;
		m_pGhost->Update();
		m_pGhost->AddTimeStamp({ m_vPos, m_vScale, m_fAngle, IsActive() });
	}
	else
	{
		m_pGhost->ResetTimeStamp();
	}
	return 0;
}

void CPlayer_TW::Late_Update(void)
{
	CObj_TW::Late_Update();
	if(m_eState != STATE::TIME_REWIND)
		m_pGhost->Late_Update();
	Update_Gravity();
}

void CPlayer_TW::Render(HDC hDC)
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	MoveToEx(hDC, (int)vRenderPos.x, (int)vRenderPos.y, nullptr);

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
	{
		vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[i]);
		LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);
	}

	vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);


	if (m_eState == STATE::TIME_REWIND)
		TextOut(hDC, (WINCX / 2) - (wcslen(L"<< 시간 되감는 중.. <<") * 4), 20, L"<< 시간 되감는 중.. <<", wcslen(L"<< 시간 되감는 중.. <<"));

	if (m_eState != STATE::TIME_REWIND)
		m_pGhost->Render(hDC);
}

void CPlayer_TW::Release(void)
{
	if (nullptr != m_pGhost)
		Safe_Delete<CGhost_TW*>(m_pGhost);
}

void CPlayer_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (m_eState == STATE::TIME_REWIND)
		return;

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_GROUND)
	{
		m_pGround = static_cast<CGround_TW*>(_pOther);
		switch (_eDir)
		{
		case COLLISION_DIR::DIR_UP:
			m_vPos.y = _pOther->GetPos().y + _pOther->GetScale().y / 2.f + m_vScale.y / 2.f;
			break;

		case COLLISION_DIR::DIR_DOWN:        
			m_fForceY = 0;
			m_vPos.y = _pOther->GetPos().y - _pOther->GetScale().y / 2.f - m_vScale.y / 2.f;
 			SetGround(true);
			break;

		case COLLISION_DIR::DIR_LEFT:
			if (!IsGround())
			{
				ChangeState(STATE::HANG);
				m_eGroundDir = _eDir;
				m_vPos.x = _pOther->GetPos().x + _pOther->GetScale().x / 2.f + m_vScale.x / 2.f;
			}
			break;
		case COLLISION_DIR::DIR_RIGHT:
			if (!IsGround())
			{
				ChangeState(STATE::HANG);
				m_eGroundDir = _eDir;
				m_vPos.x = _pOther->GetPos().x - _pOther->GetScale().x / 2.f - m_vScale.x / 2.f;
			}
			break;
		}
		
	}
}

void CPlayer_TW::Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing('A'))
	{
		m_vPos.x -= m_fSpeed * DELTA_TIME;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('D'))
	{
		m_vPos.x += m_fSpeed * DELTA_TIME;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		Shoot();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		Jump();
	}

	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		m_pScene->TimeRewind();
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_TAB))
	{
		CCamera_TW::GetInst()->ZoomIn(2.f);
	}
}

void CPlayer_TW::Jump()
{
 	ChangeState(STATE::JUMP);
	m_fForceY = -500.f;
	SetGround(false);
}

void CPlayer_TW::Jump_Hang()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_eGroundDir == COLLISION_DIR::DIR_LEFT && CKeyMgr::Get_Instance()->Key_Pressing('D'))
			m_vPos.x += 10.f;
		else if(m_eGroundDir == COLLISION_DIR::DIR_RIGHT && CKeyMgr::Get_Instance()->Key_Pressing('A'))
			m_vPos.x -= 10.f;

		Jump();
	}
}



void CPlayer_TW::Shoot()
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(GetPos());

	CLaser_TW* pLaser = new CLaser_TW;
	pLaser->Initialize();
	pLaser->SetPos(GetPos());

	D3DXVECTOR3 vDir = Get_Mouse() - vRenderPos;

	D3DXVec3Normalize(&vDir, &vDir);
	pLaser->SetDir(vDir);
	
	m_pScene->AddObj(pLaser);

	if(!IsGround())
		Jump();

}

void CPlayer_TW::Update_Gravity()
{
	if (IsGround())
	{
		m_fForceY = 0.f;
	}
	else
	{
		m_fForceY += 3.f;
	}
	m_vPos.y += m_fForceY * DELTA_TIME;
}


void CPlayer_TW::Shoot_Hang()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (m_eGroundDir == COLLISION_DIR::DIR_LEFT)
			m_vPos.x += 10.f;
		else
			m_vPos.x -= 10.f;
		Shoot();
	}
}

void CPlayer_TW::Update_Idle()
{
	Input();
}

void CPlayer_TW::Update_Move()
{
	Input();
}

void CPlayer_TW::Update_Jump()
{
	Input();
}

void CPlayer_TW::Update_Hang()
{
	m_fForceY = 0.f;
	Shoot_Hang();
	Jump_Hang();
	m_vPos.y += 50.f * DELTA_TIME;
}

void CPlayer_TW::Update_Die()
{

}

void CPlayer_TW::Update_TimeRewind()
{
	if (!m_stackTimeStamp.empty())
	{
		TIME_STAMP tStamp = m_stackTimeStamp.top();
		m_vPos = tStamp.vPos;
		m_fAngle = tStamp.fAngle;
		SetActive(tStamp.bActive);

		m_stackTimeStamp.pop();
	}
	else
	{
		ChangeState(STATE::JUMP);
	}
}

