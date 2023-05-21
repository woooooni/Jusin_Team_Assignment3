#include "stdafx.h"
#include "JItem_Bar.h"
#include "JPlayer.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "JBall.h"

CJItem_Bar::CJItem_Bar()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matTrans);
}


CJItem_Bar::~CJItem_Bar()
{
	Release();
}

void CJItem_Bar::Initialize(void)
{
	m_fAngle = 0.f;
	m_eObjType = OBJ_ITEM;

	m_tInfo.vPos = { 400.f, 250.f, 0.f };
	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 1.f };

	m_vecPoint.push_back(VECTOR{- (TILECX * 0.5f), - (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{  (TILECX * 0.5f), - (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{  (TILECX * 0.5f), + (TILECY * 0.5f), 0.f });
	m_vecPoint.push_back(VECTOR{- (TILECX * 0.5f), + (TILECY * 0.5f), 0.f });

	m_vSaveDir = m_tInfo.vDir;
	m_vecSavePoint = m_vecPoint;
}

int CJItem_Bar::Update(void)
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

void CJItem_Bar::Late_Update(void)
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

void CJItem_Bar::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(14, 180, 252));
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

void CJItem_Bar::Release(void)
{
}

void CJItem_Bar::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	switch (p_Type)
	{
	case OBJ_PLAYER:
		if (CObjMgr::Get_Inst()->Get_All(OBJ_BALL).size() < 200)
		{
			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos + VECTOR{ 0.f, -30.f, 0.f }));
			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos + VECTOR{ 20.f, -30.f, 0.f },
				VECTOR{ -1.f, -1.f, 0.f }));
			CObjMgr::Get_Inst()->Add_Obj(OBJ_BALL, CAbstractFactory<CJBall>::Create(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos + VECTOR{ -20.f, -30.f, 0.f },
				VECTOR{ 1.f, -1.f, 0.f }));
		}
		m_bDead = true;
		break;
	default:
		break;
	}
}
