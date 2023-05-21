#include "stdafx.h"
#include "LCosmos.h"
#include	"TimeMgr.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LCosmosFlower.h"


CLCosmos::CLCosmos()
{
	ZeroMemory(m_vCosmosPos, sizeof(VECTOR) * 8);
	ZeroMemory(m_pCosmos, sizeof(CObj*) * 8);

}


CLCosmos::~CLCosmos()
{
}

void CLCosmos::Initialize(void)
{
	m_tInfo.vPos = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos;

	VECTOR		vCosPos = { CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vSize.x * sqrtf(2), 0, 0 };

	MATRIX		mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(45.f));

	for (size_t i = 0; i < 8; i++)
	{
		CObj*		cosmos = CAbstractFactory<CLCosmosFlower>::Create();

		if (i % 2 == 0)
		{
			cosmos->Set_Pos(m_tInfo.vPos + vCosPos);
		}
		else
		{
			cosmos->Set_Pos(m_tInfo.vPos + (vCosPos / sqrtf(2)));
		}



		D3DXVec3TransformCoord(&vCosPos, &vCosPos, &mSrc);
		m_pCosmos[i] = cosmos;
		CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, cosmos);

	}

	m_fMaxExistTime = 3.f;
}

int CLCosmos::Update(void)
{
	if (Check_Dead())
	{
		for (auto& iter : m_pCosmos)
		{
			iter->Set_Dir({ 0, -1, 0 });
		}
		m_bDead = true;
	}

	if (CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER))
	{
		m_tInfo.vPos = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos;

		VECTOR		vCosPos = { CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vSize.x * sqrtf(2), 0, 0 };

		MATRIX		mSrc;

		D3DXMatrixRotationZ(&mSrc, D3DXToRadian(45.f));

		for (size_t i = 0; i < 8; i++)
		{
			if (i % 2 == 0)
			{
				m_pCosmos[i]->Set_Pos(m_tInfo.vPos + vCosPos);
			}
			else
			{
				m_pCosmos[i]->Set_Pos(m_tInfo.vPos + (vCosPos / sqrtf(2)));
			}

			D3DXVec3TransformCoord(&vCosPos, &vCosPos, &mSrc);

		}

	}

	m_fCreatedTime += DELTA_TIME;

	return 0;
}

void CLCosmos::Late_Update(void)
{
}

void CLCosmos::Render(HDC hDC)
{

}

void CLCosmos::Release(void)
{
}

void CLCosmos::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
