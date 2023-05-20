#include "stdafx.h"
#include "LItem.h"
#include	"TimeMgr.h"
#include	<time.h>
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LBomb.h"
#include	"LShield.h"
#include	"LFMissile.h"

CLItem::CLItem(INFO p_Info)
{
	m_tInfo = p_Info;
}


CLItem::~CLItem()
{
}

void CLItem::Initialize(void)
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };
	m_fSpeed = 100;

	m_eObjType = OBJ_ITEM;

	srand(unsigned(time(NULL)));

	int	iSrc = rand() % ITEM_END;

	m_eItemType = static_cast<LITEM_TYPE>(iSrc);

}

int CLItem::Update(void)
{

	Move();
	return 0;
}

void CLItem::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLItem::Render(HDC hDC)
{
	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);
}

void CLItem::Release(void)
{
}

void CLItem::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_PLAYER)
	{
		m_bDead = true;

		/*switch (m_eItemType)
		{
		case ITEM_BOMB:
			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLBomb>::Create());
			CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(p_Targ->Get_Info().vPos);
			break;
		case ITEM_SHIELD:
			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLShield>::Create());
			CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(p_Targ->Get_Info().vPos);
			break;
		case	ITEM_FMISSILE:
			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLFMissile>::Create());
			CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(p_Targ->Get_Info().vPos);
			static_cast<CLFMissile*>(CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT))->Set_Target();
			break;

		case ITEM_END:

			break;
		default:
			break;
		}*/
		for (int i = 0; i < 3; i++)
		{
			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLFMissile>::Create());
			CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(p_Targ->Get_Info().vPos);
			static_cast<CLFMissile*>(CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT))->Set_Target();
		}


	}
}

void CLItem::Move()
{
	if ((clamp(m_tInfo.vPos.x, m_tInfo.vSize.x * 0.5f, WINCX - m_tInfo.vSize.x * 0.5f) > m_tInfo.vPos.x && m_tInfo.vDir.x < 0)
		|| (clamp(m_tInfo.vPos.x, m_tInfo.vSize.x * 0.5f, WINCX - m_tInfo.vSize.x * 0.5f) < m_tInfo.vPos.x && m_tInfo.vDir.x > 0))
	{
		m_tInfo.vDir.x *= -1.f;
	}
	if ((clamp(m_tInfo.vPos.y, m_tInfo.vSize.y * 0.5f, WINCY - m_tInfo.vSize.y * 0.5f) > m_tInfo.vPos.y && m_tInfo.vDir.y < 0)
		|| (clamp(m_tInfo.vPos.y, m_tInfo.vSize.y * 0.5f, WINCY - m_tInfo.vSize.y * 0.5f) < m_tInfo.vPos.y && m_tInfo.vDir.y > 0))
	{
		m_tInfo.vDir.y *= -1.f;
	}


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;
}



