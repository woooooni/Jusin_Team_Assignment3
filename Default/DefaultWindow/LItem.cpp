#include "stdafx.h"
#include "LItem.h"
#include	"TimeMgr.h"
#include	<time.h>
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LBomb.h"
#include	"LShield.h"
#include	"LFMissile.h"
#include	"LBee.h"
#include	"LBulletCreator.h"
#include	<algorithm>
#include	"LKongBulle.h"
#include	"LCosmos.h"
#include	"LCosmosFlower.h"
#include	"LDecoy.h"
#include	"LCamMgr.h"
#include	"BmpMgr.h"


CLItem::CLItem(INFO p_Info)
{
	m_tInfo = p_Info;
}


CLItem::~CLItem()
{
}

void CLItem::Initialize(void)
{
	m_tInfo.vSize = {50.f, 50.f, 0.f };
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
	VECTOR vSrc = CLCamMgr::GetInst()->Get_ScreenPos(m_tInfo.vPos);

	HDC mI;

	switch (m_eItemType)
	{
	case ITEM_BOMB:
		mI = CBmpMgr::GetInst()->Get_Image(L"FlowerBomb");
		break;
	case ITEM_SHIELD:
		mI = CBmpMgr::GetInst()->Get_Image(L"Shield");

		break;
	case ITEM_FMISSILE:
		mI = CBmpMgr::GetInst()->Get_Image(L"Leaf");

		break;
	case ITEM_BEE:

		mI = CBmpMgr::GetInst()->Get_Image(L"Bee");

		break;
	case ITEM_SHOOT:

		mI = CBmpMgr::GetInst()->Get_Image(L"BabyGunDef");

		break;
	case ITEM_SHOOTROTATE:
		mI = CBmpMgr::GetInst()->Get_Image(L"BabyGunRot");

		break;
	case ITEM_KONG:
		mI = CBmpMgr::GetInst()->Get_Image(L"KongBL");

		break;
	case ITEM_COSMOS:
		mI = CBmpMgr::GetInst()->Get_Image(L"Cosmos");

		break;
	case ITEM_COSMOSBOMB:
		mI = CBmpMgr::GetInst()->Get_Image(L"CosmosBomb");

		break;
	case ITEM_DECOY:

		mI = CBmpMgr::GetInst()->Get_Image(L"Decoy");

		break;
	case ITEM_END:
		return;
	default:
		return;
	}

	GdiTransparentBlt(hDC,
		(int)(vSrc.x - m_tInfo.vSize.x * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
		(int)(vSrc.y - m_tInfo.vSize.y * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
		m_tInfo.vSize.x * CLCamMgr::GetInst()->Get_Scale(),
		m_tInfo.vSize.y * CLCamMgr::GetInst()->Get_Scale(), mI, 0, 0, m_tInfo.vSize.x, m_tInfo.vSize.y, RGB(255,255,255)
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

		INFO	p_Info, p_Info2;

		VECTOR	vSrc;


		switch (m_eItemType)
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
			for (int i = 0; i < 3; i++)
			{
				CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLFMissile>::Create());
				CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(p_Targ->Get_Info().vPos);
				static_cast<CLFMissile*>(CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT))->Set_Target();
			}
			break;

		case	ITEM_BEE:

		p_Info.vPos = p_Targ->Get_Info().vPos, p_Info2.vPos = p_Targ->Get_Info().vPos;

		p_Info.vSize = { 100, 100, 0 };
		p_Info2.vSize = { 100 * sqrtf(3), 100 * sqrtf(3), 0 };

		p_Info.vPos += {0, -1.f * (p_Info.vSize.x + p_Info2.vSize.x) * 0.25f, 0};
		p_Info2.vPos += {0, (p_Info.vSize.x + p_Info2.vSize.x) * 0.25f, 0};

		CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLBee>::Create(p_Info));
		CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLBee>::Create(p_Info2));

		break;

		case ITEM_SHOOT:

			if (!CObjMgr::Get_Inst()->Get_All(OBJ_UTIL).empty())
			{
				auto iter = find_if(CObjMgr::Get_Inst()->Get_All(OBJ_UTIL).begin(), CObjMgr::Get_Inst()->Get_All(OBJ_UTIL).end(), [&](auto& iter)->bool
				{
					auto src = dynamic_cast<CLBulletCreator*>(iter);
					if (!src)
						return false;

					return !src->Get_RotateCreate();
				});

				if (iter == CObjMgr::Get_Inst()->Get_All(OBJ_UTIL).end())
					CObjMgr::Get_Inst()->Add_Obj(OBJ_UTIL, CAbstractFactory<CLBulletCreator>::Create());
				else
					dynamic_cast<CLBulletCreator*>(*iter)->Add_ExistTime();

			}
			else
				CObjMgr::Get_Inst()->Add_Obj(OBJ_UTIL, CAbstractFactory<CLBulletCreator>::Create());

			break;

		case ITEM_SHOOTROTATE:

			CObjMgr::Get_Inst()->Add_Obj(OBJ_UTIL, CAbstractFactory<CLBulletCreator>::Create());
			static_cast<CLBulletCreator*>(CObjMgr::Get_Inst()->Get_Last(OBJ_UTIL))->Set_RotateCreate();
			break;

		case	ITEM_KONG:
			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLKongBulle>::Create());

			break;

		case	ITEM_COSMOS:

			CObjMgr::Get_Inst()->Add_Obj(OBJ_UTIL, CAbstractFactory<CLCosmos>::Create());


			break;

		case	ITEM_COSMOSBOMB:

			vSrc = VECTOR((WINCX * 0.5f), (WINCY + 0.5), 0);



			for (size_t i = 0; i < 7; i++)
			{
				CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLCosmosFlower>::Create());

				CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Pos(vSrc);
				CObjMgr::Get_Inst()->Get_Last(OBJ_EFFECT)->Set_Dir({ 0, -1, 0 });

				if (i % 2 == 0)
				{

					vSrc += VECTOR(COSMOSX - 10, 0, 0) * (i + 1);

				}
				else
				{
					vSrc -= VECTOR(COSMOSX - 10, 0, 0) * (i + 1);

				}
			}


			break;

		case	ITEM_DECOY:

			CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLDecoy>::Create());

			break;

		case ITEM_END:

			break;
		default:
			break;
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



