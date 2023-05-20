#include "stdafx.h"
#include "Monster_TW.h"
#include "Camera_TW.h"
#include "TimeMgr.h"
#include "Bullet_TW.h"
#include "Scene_Taewon.h"
CMonster_TW::CMonster_TW()
	:CObj_TW(OBJ_TYPE::OBJ_MONSTER)
	, m_fForceY(0.f)
	, m_pScene(nullptr)
	, m_fDeletionTime(2.f)
	, m_fAccDeletion(0.f)
	, m_fFireDelayTime(3.f)
	, m_fAccFire(3.f)
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

	ChangeState(STATE::JUMP);
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

	float fMagnification = CCamera_TW::GetInst()->GetMagnification();
	D3DXMatrixScaling(&matScale, 1.f * fMagnification, 1.f * fMagnification, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	if (m_eState != STATE::TIME_REWIND)
		Update_TimeStamp();

	return 0;
}

void CMonster_TW::Late_Update(void)
{

}

void CMonster_TW::Render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	MoveToEx(hDC, (int)vRenderPos.x, (int)vRenderPos.y, nullptr);

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
	{
		vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[i]);
		LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);
	}

	vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);


	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void CMonster_TW::Release(void)
{

}

void CMonster_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (m_eState == STATE::TIME_REWIND)
		return;

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_LASER)
	{
		if (_eDir == COLLISION_DIR::DIR_LEFT)
		{
			ChangeState(STATE::DIE);
			CCamera_TW::GetInst()->SetTargetObj(this);
			m_vDeadDir = D3DXVECTOR3{ -1.f, 0.f, 0.f };
		}
		else if (_eDir == COLLISION_DIR::DIR_RIGHT)
		{
			ChangeState(STATE::DIE);
			CCamera_TW::GetInst()->SetTargetObj(this);
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


void CMonster_TW::Update_Idle()
{
	if (nullptr != m_pTarget)
	{
		D3DXVECTOR3 vLen = m_pTarget->GetPos() - GetPos();
		if (D3DXVec3Length(&vLen) < 300)
		{
			m_fAccFire += DELTA_TIME;
			if (m_fAccFire >= m_fFireDelayTime)
			{
				m_fAccFire = 0.f;
				CBullet_TW* pBullet = new CBullet_TW;
				pBullet->SetPos(GetPos());
				D3DXVec3Normalize(&vLen, &vLen);
				pBullet->SetDir(vLen);
				pBullet->Initialize();
				m_pScene->AddObj(pBullet);
			}
		}
	}
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
	if (!IsActive())
		return;

	CTimeMgr::GetInst()->SetTimeScale(0.5f);
	m_vPos += m_vDeadDir * 1000.f * DELTA_TIME;

	m_fAccDeletion += DELTA_TIME;
	if (m_fAccDeletion >= m_fDeletionTime)
	{
		CTimeMgr::GetInst()->SetTimeScale(1.f);
		SetActive(false);
		m_fAccDeletion = 0.f;
	}
}

void CMonster_TW::Update_TimeRewind()
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

