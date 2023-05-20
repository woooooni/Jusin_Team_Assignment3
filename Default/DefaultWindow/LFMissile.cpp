#include "stdafx.h"
#include "LFMissile.h"
#include	"TimeMgr.h"
#include	<time.h>
#include	"ObjMgr.h"


CLFMissile::CLFMissile() : m_pTarg(nullptr)
{
}


CLFMissile::~CLFMissile()
{
}

void CLFMissile::Initialize(void)
{
	m_eItemType = ITEM_FMISSILE;
	m_tInfo.vSize = { 80, 80, 0 };
	m_tInfo.vDir = { 1,0,0 };

	m_vSubCircleCenter = { 20, 0, 0 };
	m_vSubCircleRad = 60.f;

	m_fSpeed = 200.f;

	m_fCreatedTime = 0.f;
	m_fMaxExistTime = 0.f;
}

int CLFMissile::Update(void)
{
	if (Check_Dead())
		return 1;

	if (m_fMaxExistTime == 0.f)
	{

		Follow_Target();

		if (m_pTarg)
		{
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;

		}

	}
	else
		m_fCreatedTime += DELTA_TIME;


	MATRIX	mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(270.f * DELTA_TIME));

	D3DXVec3TransformCoord(&m_vSubCircleCenter, &m_vSubCircleCenter, &mSrc);

	return 0;
}

void CLFMissile::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;

	if ((!m_pTarg || m_pTarg->Get_Dead()) && m_fMaxExistTime == 0)
	{
		if (CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).empty())
		{
			if (m_pTarg)
				m_pTarg = nullptr;

			return;

		}

		bool bAllDead = true;

		for (auto& iter : CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER))
		{
			if (!iter->Get_Dead())
			{
				bAllDead = false;
				break;
			}
		}

		if (bAllDead)
		{
			if (m_pTarg)
				m_pTarg = nullptr;

			return;
		}

		auto iter = CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).begin();

		while (true)
		{
			int		iIndex = rand() % CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).size();



			for (int i = 0; i < iIndex; i++)
			{
				iter++;
			}

			if (!(*iter)->Get_Dead())
				break;

			iter = CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).begin();
		}


		m_pTarg = *iter;
	}

}

void CLFMissile::Render(HDC hDC)
{
	HPEN hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);

	HBRUSH myB = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);




	Ellipse(hDC,
		(int)(m_tInfo.vPos.x + m_vSubCircleCenter.x - m_vSubCircleRad * 0.5f),
		(int)(m_tInfo.vPos.y + m_vSubCircleCenter.y - m_vSubCircleRad * 0.5f),
		(int)(m_tInfo.vPos.x + m_vSubCircleCenter.x + m_vSubCircleRad * 0.5f),
		(int)(m_tInfo.vPos.y + m_vSubCircleCenter.y + m_vSubCircleRad * 0.5f)
		);

	SelectObject(hDC, oldPen);
	DeleteObject(hPen);

}

void CLFMissile::Release(void)
{
}

void CLFMissile::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_MONSTER && m_fMaxExistTime == 0 && p_Targ == m_pTarg && !p_Targ->Get_Dead())
	{
		m_tInfo.vSize *= 2.f;

		m_vSubCircleCenter *= 2.f;

		m_vSubCircleRad *= 2.f;

		m_fMaxExistTime = 3.f;
	}
}

void CLFMissile::Set_Target()
{
	if (CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).empty())
		return;


	bool bAllDead = true;

	for (auto& iter : CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER))
	{
		if (!iter->Get_Dead())
		{
			bAllDead = false;
			break;
		}
	}

	if (bAllDead)
	{
		return;
	}

	auto iter = CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).begin();

	while (true)
	{
		int		iIndex = rand() % CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).size();



		for (int i = 0; i < iIndex; i++)
		{
			iter++;
		}

		if (!(*iter)->Get_Dead())
			break;

		iter = CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER).begin();
	}

	
	m_pTarg = *iter;

	m_tInfo.vDir = m_pTarg->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	MATRIX		mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(30.f));

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mSrc);

}

void CLFMissile::Follow_Target()
{
	if (m_pTarg == nullptr)
		return;

	VECTOR		targDir = m_pTarg->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&targDir, &targDir);

	float		fCos = D3DXVec3Dot(&targDir, &m_tInfo.vDir);

	float		fAngle = acosf(fCos);

	VECTOR	vTmp;

	D3DXVec3Cross(&vTmp, &m_tInfo.vDir, &targDir);

	if (vTmp.z < 0)
		fAngle *= -1.f;

	if (fabs(fAngle) <= D3DXToRadian(10.f))
	{
		if (fabs(fAngle) <= 1.f)
			return;
		else
			fAngle = fAngle >= 0 ? D3DXToRadian(10.f) : D3DXToRadian(-10.f);
	}

	MATRIX		mSrc;

	D3DXMatrixRotationZ(&mSrc, fAngle * 2.f * DELTA_TIME);

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mSrc);

}
