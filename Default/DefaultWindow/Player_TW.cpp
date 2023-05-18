#include "stdafx.h"
#include "Player_TW.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Camera_TW.h"
#include "Laser_TW.h"
#include "SceneMgr.h"
CPlayer_TW::CPlayer_TW()
	: CObj_TW(OBJ_TYPE::OBJ_PLAYER)
	, m_fForceY(0.f)
	, m_pScene(nullptr)
	, m_eState(STATE::JUMP)
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
}

int CPlayer_TW::Update(void)
{
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
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	return 0;
}

void CPlayer_TW::Late_Update(void)
{

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

	vRenderPos = CCamera_TW::GetInst()->GetRenderPos(GetPos());
	Ellipse(hDC,
		int(vRenderPos.x - 10.f),
		int(vRenderPos.y - 10.f),
		int(vRenderPos.x + 10.f),
		int(vRenderPos.y + 10.f));

	D3DXVECTOR3 vMousePos = Get_Mouse();

	Ellipse(hDC,
		int(vMousePos.x - 10.f),
		int(vMousePos.y - 10.f),
		int(vMousePos.x + 10.f),
		int(vMousePos.y + 10.f));
}

void CPlayer_TW::Release(void)
{

}



void CPlayer_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_GROUND)
	{
		switch (_eDir)
		{
		case COLLISION_DIR::DIR_DOWN:
			if (!IsGround())
			{
				ChangeState(STATE::IDLE);
				SetGround(true);
			}
			break;
		case COLLISION_DIR::DIR_LEFT:
		case COLLISION_DIR::DIR_RIGHT:
			if (!IsGround())
			{
				ChangeState(STATE::HANG);
				m_eGroundDir = _eDir;
			}
			else
			{
				if (_eDir == COLLISION_DIR::DIR_LEFT)
					m_vPos.x = _pOther->GetPos().x + _pOther->GetScale().x / 2.f + m_vScale.x / 2.f;
				else
					m_vPos.x = _pOther->GetPos().x - _pOther->GetScale().x / 2.f - m_vScale.x / 2.f;
			}
			break;
		}	
	}
}

void CPlayer_TW::ChangeState(STATE _eState)
{
	if (m_eState == _eState)
		return;

	m_eState = _eState;
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
}

void CPlayer_TW::Jump()
{
 	ChangeState(STATE::JUMP);
	m_fForceY = -1300.f;
}

void CPlayer_TW::Jump_Hang()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (m_eGroundDir == COLLISION_DIR::DIR_LEFT)
			m_vPos.x += 10.f;
		else
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

	if (m_fForceY < 0.f)
		m_fForceY += 900.f * DELTA_TIME;
	else
		m_fForceY -= 900.f * DELTA_TIME;
	
	if (m_fForceY < 980.f)
		SetGround(false);

	m_vPos.y += m_fForceY * DELTA_TIME;
	m_vPos.y += 980.f * DELTA_TIME;
}

void CPlayer_TW::Update_Hang()
{
	Shoot_Hang();
	Jump_Hang();
	m_vPos.y += 50.f * DELTA_TIME;
}

void CPlayer_TW::Update_Die()
{

}

void CPlayer_TW::Update_TimeRewind()
{
}

