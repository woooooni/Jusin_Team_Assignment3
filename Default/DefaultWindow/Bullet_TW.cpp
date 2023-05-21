#include "stdafx.h"
#include "Bullet_TW.h"
#include "Camera_TW.h"
#include "TimeMgr.h"
#include "Monster_TW.h"
#include "Player_TW.h"
#include "SoundMgr.h"

CBullet_TW::CBullet_TW()
	:CObj_TW(OBJ_TYPE::OBJ_BULLET)
	, m_vDir()
	, m_fBulletSpeed(500.f)
	, m_fDeletionTime(3.f)
	, m_fAccDeletion(0.f)
{

}


CBullet_TW::~CBullet_TW()
{
}

void CBullet_TW::Initialize(void)
{
	SetScale({ 10.f, 20.f, 0.f });

	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });

	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
		m_vecVertices.push_back(m_vecOriginVertices[i]);

	D3DXVECTOR3 vUp = { 0.f, -1.f, 0.f };
	m_fAngle = acos(D3DXVec3Dot(&m_vDir, &vUp));
	if (m_vDir.x < 0.f)
		m_fAngle *= -1;

	ChangeState(STATE::IDLE);
}

int CBullet_TW::Update(void)
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
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	if (m_eState != STATE::TIME_REWIND)
		Update_TimeStamp();
	return 0;
}

void CBullet_TW::Late_Update(void)
{
	CObj_TW::Late_Update();
}

void CBullet_TW::Render(HDC hDC)
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

void CBullet_TW::Release(void)
{
}

void CBullet_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (m_eState == STATE::TIME_REWIND || m_eState == STATE::DIE)
		return;

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_PLAYER && GetObjType() == OBJ_TYPE::OBJ_MONSTER_BULLET)
	{
		if (_eDir == COLLISION_DIR::DIR_LEFT)
			static_cast<CPlayer_TW*>(_pOther)->OnDamaged(COLLISION_DIR::DIR_RIGHT, this);
		else
			static_cast<CPlayer_TW*>(_pOther)->OnDamaged(COLLISION_DIR::DIR_LEFT, this);

		ChangeState(STATE::DIE);
		SetActive(false);
	}

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_MONSTER && GetObjType() == OBJ_TYPE::OBJ_PLAYER_BULLET)
	{
		if (_eDir == COLLISION_DIR::DIR_LEFT)
			static_cast<CMonster_TW*>(_pOther)->OnDamaged(COLLISION_DIR::DIR_RIGHT, this);
		else
			static_cast<CMonster_TW*>(_pOther)->OnDamaged(COLLISION_DIR::DIR_LEFT, this);

		ChangeState(STATE::DIE);
		SetActive(false);
	}
}


void CBullet_TW::Update_Idle()
{
	m_vPos += m_vDir * m_fBulletSpeed * DELTA_TIME;

	m_fAccDeletion += DELTA_TIME;
	if (m_fAccDeletion >= m_fDeletionTime)
	{
		SetActive(false);
		ChangeState(STATE::DIE);
	}
}

void CBullet_TW::Update_Move()
{

}

void CBullet_TW::Update_Jump()
{
}

void CBullet_TW::Update_Hang()
{
}

void CBullet_TW::Update_Die()
{
}

void CBullet_TW::Update_TimeRewind()
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
		SetDelete(true);
	}
}

void CBullet_TW::Parrying()
{
	SetObjType(OBJ_TYPE::OBJ_PLAYER_BULLET);
	m_vDir *= -1;

	CSoundMgr::GetInst()->StopSound(CHANNELID::SOUND_PARRING);
	CSoundMgr::GetInst()->PlaySound(L"Parring.wav", CHANNELID::SOUND_PARRING, 1.f);
}

