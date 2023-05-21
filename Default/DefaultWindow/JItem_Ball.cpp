#include "stdafx.h"
#include "JItem_Ball.h"
#include "JBall.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "JBall.h"

CJItem_Ball::CJItem_Ball()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);
}


CJItem_Ball::~CJItem_Ball()
{
	Release();
}

void CJItem_Ball::Initialize(void)
{
	m_fAngle = 0.f;
	m_eObjType = OBJ_ITEM;

	m_tInfo.vPos = { 400.f, 250.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };

	m_vecPoint.push_back(VECTOR{ - (TILECX * 0.5f), - (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{   (TILECX * 0.5f), - (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{   (TILECX * 0.5f), (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{ - (TILECX * 0.5f), (TILECY * 0.5f), 0.f });

	m_vSaveDir = m_tInfo.vDir;
	m_vecSavePoint = m_vecPoint;
}

int CJItem_Ball::Update(void)
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

	m_tInfo.vDir = m_vSaveDir;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_matWorld);

	return 0;
}

void CJItem_Ball::Late_Update(void)
{
	m_fSpeed = 300.f * DELTA_TIME;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	VECTOR newPos = m_tInfo.vPos + m_tInfo.vDir * m_fSpeed;

	if (newPos.y >= WINCY + (TILECY * 0.5))
	{
		Set_Dead();
		return;
	}

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
}

void CJItem_Ball::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 165, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Rectangle(hDC,
		m_tInfo.vPos.x - (TILECX * 0.5),
		m_tInfo.vPos.y - (TILECY * 0.5),
		m_tInfo.vPos.x + (TILECX * 0.5),
		m_tInfo.vPos.y + (TILECY * 0.5)
	);
	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CJItem_Ball::Release(void)
{
}

void CJItem_Ball::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	switch (p_Type)
	{
	case OBJ_PLAYER:
		if (!CObjMgr::Get_Inst()->Get_All(OBJ_BALL).empty() && CObjMgr::Get_Inst()->Get_All(OBJ_BALL).size() <= 100)
		{
			const VECTOR& lastBallPos = CObjMgr::Get_Inst()->Get_Last(OBJ_BALL)->Get_Info().vPos;
			const VECTOR& lastBallDir = CObjMgr::Get_Inst()->Get_Last(OBJ_BALL)->Get_Info().vDir;

			const VECTOR& frontBallPos = CObjMgr::Get_Inst()->Get_All(OBJ_BALL).front()->Get_Info().vPos;
			const VECTOR& frontBallDir = CObjMgr::Get_Inst()->Get_All(OBJ_BALL).front()->Get_Info().vDir;

			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(lastBallPos,
				lastBallDir + VECTOR{ -0.5f, -0.5f, 0.f }));

			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(lastBallPos,
				lastBallDir + VECTOR{ 0.5f, -0.5f, 0.f }));
			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(frontBallPos,
				frontBallDir + VECTOR{ -0.5f, -0.5f, 0.f }));

			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(frontBallPos,
				frontBallDir + VECTOR{ 0.5f, -0.5f, 0.f }));
		}
		m_bDead = true;
		break;
	default:
		break;
	}

}
