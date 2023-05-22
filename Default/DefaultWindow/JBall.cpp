#include "stdafx.h"
#include "JBall.h"
#include "TimeMgr.h"
#include "Well512Random.h"
#include "JPlayer.h"
#include "JTileMgr.h"
#include "JCollisionMgr.h"

CJBall::CJBall()
	: m_bDirChange(false), m_fRad(5.f), m_iSpeedCount(0), m_fTimeSpeed(300.f), m_bColi(false), m_eDir(DIR_END)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);
}

CJBall::~CJBall()
{
	Release();
}

void CJBall::Initialize(void)
{
	m_fAngle = 0.f;
	m_eObjType = OBJ_BALL;

	m_tInfo.vDir = { 0.f,  -1.f, 0.f };

	m_tInfo.vPos = { 400.f, 500.f, 0.f };
	
	m_tInfo.vSize = { 1.f, 1.f, 1.f };

	m_vecPoint.push_back(VECTOR{ -m_fRad, -m_fRad, 0.f });
	m_vecPoint.push_back(VECTOR{ m_fRad, -m_fRad, 0.f });
	m_vecPoint.push_back(VECTOR{ m_fRad,  m_fRad, 0.f });
	m_vecPoint.push_back(VECTOR{ -m_fRad,  m_fRad, 0.f });

	m_vecSavePoint = m_vecPoint;
}

int CJBall::Update(void)
{
	D3DXMatrixScaling(&m_matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixRotationZ(&m_matRot, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&m_matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_matWorld = m_matScale * m_matRot * m_matTrans;

	for (int i = 0; i < m_vecPoint.size(); ++i)
	{
		m_vecPoint[i] = m_vecSavePoint[i];
		D3DXVec3TransformCoord(&m_vecPoint[i], &m_vecPoint[i], &m_matWorld);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_matWorld);

	return 0;
}

void CJBall::Late_Update(void)
{
	static CWell512Random randomb(UINT(time(NULL)));

	UINT iRandom = randomb.Next(2);

	m_fSpeed = m_fTimeSpeed * DELTA_TIME;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	VECTOR newPos = m_tInfo.vPos + m_tInfo.vDir * m_fSpeed;

	if (newPos.x >= WINCX - m_fRad)
	{
		m_tInfo.vDir.x *= -1.0f;
	}
	if (newPos.x <= m_fRad)
	{
		m_tInfo.vDir.x *= -1.0f;
	}
	if (newPos.y <= m_fRad)
	{
		m_tInfo.vDir.y *= -1.0f;
	}
	if (m_tInfo.vDir.y == 0)
	{
		if(iRandom == 0)
			m_tInfo.vDir.y += 1.f;
		else
			m_tInfo.vDir.y -= 1.f;
	}
	if (newPos.y >= WINCY + m_fRad)
	{
		Set_Dead();
		return;
	}

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	Tile_Coli();
}

void CJBall::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)m_tInfo.vPos.x - (int)m_fRad,
		(int)m_tInfo.vPos.y - (int)m_fRad,
		(int)m_tInfo.vPos.x + (int)m_fRad,
		(int)m_tInfo.vPos.y + (int)m_fRad );

	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CJBall::Release(void)
{
}

void CJBall::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	CWell512Random random(UINT(time(NULL)));

	UINT iRandom = random.Next(2);

	VECTOR vDis = m_tInfo.vPos - p_Targ->Get_Info().vPos;
	float fDis = D3DXVec3Length(&vDis);

	switch (p_Type)
	{
	case OBJ_PLAYER:
		switch (m_eDir)
		{
		case DIR_TOP:
			if (m_tInfo.vDir.y > 0)
				m_tInfo.vDir.y *= -1.f;
			break;
		case DIR_BOTTOM:
			if (m_tInfo.vDir.y < 0)
				m_tInfo.vDir.y *= -1.f;
			break;
		case DIR_LEFT:
			if (m_tInfo.vDir.x > 0)
				m_tInfo.vDir.x *= -1.f;
			m_tInfo.vDir.y *= -1.f;
			break;
		case DIR_RIGHT:
			if (m_tInfo.vDir.x < 0)
				m_tInfo.vDir.x *= -1.f;
			m_tInfo.vDir.y *= -1.f;
			break;
		default:
			break;
		}
		break;

		if (static_cast<CJPlayer*>(p_Targ)->Get_TimeSpeed() <= 350.f)
			m_fTimeSpeed -= 20.f;
		else if (static_cast<CJPlayer*>(p_Targ)->Get_TimeSpeed() > 350.f)
			m_fTimeSpeed += 20.f;

		if (m_fTimeSpeed <= 300)
			m_fTimeSpeed = 300.f;
		if (m_fTimeSpeed >= 500)
			m_fTimeSpeed = 500.f;

		break;

	case OBJ_TILE:
		switch (m_eDir)
		{
		case DIR_TOP:
			if (m_tInfo.vDir.y > 0)
				m_tInfo.vDir.y *= -1.f;
			break;
		case DIR_BOTTOM:
			if (m_tInfo.vDir.y < 0)
				m_tInfo.vDir.y *= -1.f;
			break;
		case DIR_LEFT:
			if (m_tInfo.vDir.x > 0)
				m_tInfo.vDir.x *= -1.f;
			break;
		case DIR_RIGHT:
			if (m_tInfo.vDir.x < 0)
				m_tInfo.vDir.x *= -1.f;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}

void CJBall::Tile_Coli()
{
	CObj* pTile = CJTileMgr::Get_Instance()->Get_Tile(this);

	CJCollisionMgr::TestTile(this, pTile);
}
