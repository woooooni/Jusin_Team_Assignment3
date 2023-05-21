#include "stdafx.h"
#include "JTile.h"
#include "JItem_Ball.h"
#include "JItem_Bar.h"
#include "AbstractFactory.h"
#include "Well512Random.h"
#include "ObjMgr.h"

CJTile::CJTile()
	: m_iDrawID(0), m_iOption(0), m_bStart(true)
{
}


CJTile::~CJTile()
{
	Release();
}

void CJTile::Initialize(void)
{
	m_eObjType = OBJ_TILE;

	
}

int CJTile::Update(void)
{
	if (m_bStart)
	{
		m_vecPoint.push_back(VECTOR{ m_tInfo.vPos.x - (TILECX * 0.5f), m_tInfo.vPos.y - (TILECY * 0.5f), 0.f });
		m_vecPoint.push_back(VECTOR{ m_tInfo.vPos.x + (TILECX * 0.5f), m_tInfo.vPos.y - (TILECY * 0.5f), 0.f });
		m_vecPoint.push_back(VECTOR{ m_tInfo.vPos.x + (TILECX * 0.5f), m_tInfo.vPos.y + (TILECY * 0.5f), 0.f });
		m_vecPoint.push_back(VECTOR{ m_tInfo.vPos.x - (TILECX * 0.5f), m_tInfo.vPos.y + (TILECY * 0.5f), 0.f });

		m_bStart= false;
	}

	return 0;
}

void CJTile::Late_Update(void)
{
}

void CJTile::Render(HDC hDC)
{
	if (m_iDrawID == 2)
	{
		HBRUSH myB = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

		Rectangle(hDC,
			(int)m_vecPoint[0].x,
			(int)m_vecPoint[0].y,
			(int)m_vecPoint[2].x,
			(int)m_vecPoint[2].y
		);
		SelectObject(hDC, oldB);
		DeleteObject(myB);
	}
	else if(m_iDrawID == 1)
	{
		Rectangle(hDC,
			(int)m_vecPoint[0].x,
			(int)m_vecPoint[0].y,
			(int)m_vecPoint[2].x,
			(int)m_vecPoint[2].y
		);
	}
	
}

void CJTile::Release(void)
{
}

void CJTile::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	switch (p_Type)
	{
	case OBJ_BALL:
	{
		if (m_iDrawID == 1)
		{
			static CWell512Random random(UINT(time(NULL)));

			UINT iRandom = random.Next(1, 101);

			if (iRandom <= 20) 
				CObjMgr::Get_Inst()->Add_Obj(OBJ_ITEM, CAbstractFactory<CJItem_Bar>::Create(this->Get_Info().vPos));
			else if (iRandom >= 80)  
				CObjMgr::Get_Inst()->Add_Obj(OBJ_ITEM, CAbstractFactory<CJItem_Ball>::Create(this->Get_Info().vPos));


			Set_Dead();
		}
	}
		break;
	default:
		break;
	}
}
