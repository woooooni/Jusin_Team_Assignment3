#include "stdafx.h"
#include "Laser_TW.h"
#include "Camera_TW.h"
#include "TimeMgr.h"
#include "Monster_TW.h"
#include "Bullet_TW.h"
CLaser_TW::CLaser_TW()
	:CObj_TW(OBJ_TYPE::OBJ_LASER)
	, m_fLen(300.f)
	, m_bAttacked(false)
{
}


CLaser_TW::~CLaser_TW()
{
	
}

void CLaser_TW::Initialize(void)
{
	m_fSpeed = 3000.f;
	SetScale(D3DXVECTOR3{ 30.f, 30.f, 0.f });

	ChangeState(STATE::IDLE);
}

int CLaser_TW::Update(void)
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

	if (m_eState != STATE::TIME_REWIND)
		Update_TimeStamp();

	return 0;
}

void CLaser_TW::Late_Update(void)
{
	CObj_TW::Late_Update();
}

void CLaser_TW::Render(HDC hDC)
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(GetPos());

	HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);


	MoveToEx(hDC,	int(vRenderPos.x - m_vDir.x * m_fLen), int(vRenderPos.y - m_vDir.y * m_fLen), nullptr);
	LineTo(hDC,		int(vRenderPos.x + m_vDir.x * m_fLen), int(vRenderPos.y + m_vDir.y * m_fLen));

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void CLaser_TW::Release(void)
{

}

void CLaser_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	if (m_bAttacked)
		return;

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_MONSTER)
	{
		CMonster_TW* pMonster = static_cast<CMonster_TW*>(_pOther);

		if(_eDir == COLLISION_DIR::DIR_LEFT)
			pMonster->OnDamaged(COLLISION_DIR::DIR_RIGHT, this);
		else
			pMonster->OnDamaged(COLLISION_DIR::DIR_LEFT, this);
		
		m_bAttacked = true;
	}

	if (_pOther->GetObjType() == OBJ_TYPE::OBJ_MONSTER_BULLET)
	{
		CBullet_TW* pBullet = static_cast<CBullet_TW*>(_pOther);
		pBullet->Parrying();
		m_bAttacked = true;
	}
}


void CLaser_TW::Update_Idle()
{
	m_vPos += m_vDir * m_fSpeed * DELTA_TIME;
}

void CLaser_TW::Update_Move()
{
}

void CLaser_TW::Update_Jump()
{
}

void CLaser_TW::Update_Hang()
{
}

void CLaser_TW::Update_Die()
{
}

void CLaser_TW::Update_TimeRewind()
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

