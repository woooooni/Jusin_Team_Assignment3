#include "stdafx.h"
#include "JPlayer.h"
#include "TimeMgr.h"

CJPlayer::CJPlayer()
	: m_fTimeSpeed(150.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);
}


CJPlayer::~CJPlayer()
{
	Release();
}

void CJPlayer::Initialize(void)
{
	m_fAngle = 0.f;
	m_eObjType = OBJ_PLAYER;

	m_tInfo.vPos = { 400.f, 550.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };

	m_vecPoint.push_back(VECTOR{ -50.f, -10.f, 0.f });
	m_vecPoint.push_back(VECTOR{  50.f, -10.f, 0.f });
	m_vecPoint.push_back(VECTOR{  50.f,  10.f, 0.f });
	m_vecPoint.push_back(VECTOR{ -50.f,  10.f, 0.f });

	m_vSaveDir = m_tInfo.vDir;
	m_vecSavePoint = m_vecPoint;
}

int CJPlayer::Update(void)
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

	//m_tInfo.vDir = m_vSaveDir;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_matWorld);
	
	return 0;
}

void CJPlayer::Late_Update(void)
{
	VECTOR vSrc = ::Get_Mouse() - m_tInfo.vPos;

	float fDis = D3DXVec3Length(&vSrc);

	if (0.f <= fDis && 100.f > fDis)
		m_fTimeSpeed = 150.f;
	else if (100.f <= fDis && 200.f > fDis)
		m_fTimeSpeed = 250.f;
	else if (200.f <= fDis && 300.f > fDis)
		m_fTimeSpeed = 350.f;
	else if (300.f <= fDis && 400.f > fDis)
		m_fTimeSpeed = 450.f;
	else if (400.f <= fDis && 500.f > fDis)
		m_fTimeSpeed = 550.f;
	else if (500.f <= fDis)
		m_fTimeSpeed = 650.f;

	m_fSpeed = m_fTimeSpeed * DELTA_TIME;
	if (vSrc.x >= 0)
		m_tInfo.vDir = { 1, 0, 0 };
	else
		m_tInfo.vDir = { -1, 0, 0 };


	VECTOR newPos = m_tInfo.vPos + m_tInfo.vDir * m_fSpeed;

	if(WINCX <= newPos.x + 51.f || 0 >= newPos.x - 51.f)
		m_fSpeed = 0.f;

	m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed;
	//m_fAngle = D3DXVec3Dot(&m_tInfo.vDir, &VECTOR{ 0.f, 0.f, 0.f });
}

void CJPlayer::Render(HDC hDC)
{
	for (UINT i = 0; i < m_vecPoint.size(); ++i)
	{
		MoveToEx(hDC, int(m_vecPoint[i].x), int(m_vecPoint[i].y), nullptr);

		if (i < m_vecPoint.size() - 1)
			LineTo(hDC, int(m_vecPoint[i + 1].x), int(m_vecPoint[i + 1].y));
		else
			LineTo(hDC, int(m_vecPoint[0].x), int(m_vecPoint[0].y));
	}
}

void CJPlayer::Release(void)
{
}

void CJPlayer::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	switch (p_Type)
	{
	case OBJ_ITEM:
		break;
	default:
		break;
	}
}
