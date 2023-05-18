#include "stdafx.h"
#include "Monster_TW.h"
#include "Camera_TW.h"
#include "TimeMgr.h"

CMonster_TW::CMonster_TW()
	:CObj_TW(OBJ_TYPE::OBJ_MONSTER)
	, m_fForceY(0.f)
	, m_pScene(nullptr)
	, m_eState(STATE::JUMP)
{

}


CMonster_TW::~CMonster_TW()
{

}

void CMonster_TW::Initialize(void)
{
	SetScale(D3DXVECTOR3{ 30.f, 30.f, 0.f });

	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });

	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
		m_vecVertices.push_back(m_vecOriginVertices[i]);
}

int CMonster_TW::Update(void)
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

void CMonster_TW::Late_Update(void)
{

}

void CMonster_TW::Render(HDC hDC)
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
}

void CMonster_TW::Release(void)
{

}

void CMonster_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_LASER)
	{
		if (_eDir == COLLISION_DIR::DIR_LEFT)
		{
			ChangeState(STATE::DIE);
			m_vDeadDir = D3DXVECTOR3{ -1.f, 0.f, 0.f };
		}
		else if (_eDir == COLLISION_DIR::DIR_RIGHT)
		{
			ChangeState(STATE::DIE);
			m_vDeadDir = D3DXVECTOR3{ 1.f, 0.f, 0.f };
		}
	}

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
			if (_eDir == COLLISION_DIR::DIR_LEFT)
				m_vPos.x = _pOther->GetPos().x + _pOther->GetScale().x / 2.f + m_vScale.x / 2.f;
			else
				m_vPos.x = _pOther->GetPos().x - _pOther->GetScale().x / 2.f - m_vScale.x / 2.f;
			break;
		}
	}
}

void CMonster_TW::ChangeState(STATE _eState)
{
	if (m_eState == _eState)
		return;

	if (m_eState == STATE::DIE)
		return;

	m_eState = _eState;
}

void CMonster_TW::Update_Idle()
{

}

void CMonster_TW::Update_Move()
{

}

void CMonster_TW::Update_Jump()
{
	if (m_fForceY < 0.f)
		m_fForceY += 900.f * DELTA_TIME;
	else
		m_fForceY -= 900.f * DELTA_TIME;

	if (m_fForceY < 980.f)
		SetGround(false);

	m_vPos.y += m_fForceY * DELTA_TIME;
	m_vPos.y += 980.f * DELTA_TIME;
}

void CMonster_TW::Update_Hang()
{

}

void CMonster_TW::Update_Die()
{
	m_vPos += m_vDeadDir * 500.f * DELTA_TIME;
}

void CMonster_TW::Update_TimeRewind()
{

}

