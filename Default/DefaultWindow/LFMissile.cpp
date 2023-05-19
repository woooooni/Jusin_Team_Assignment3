#include "stdafx.h"
#include "LFMissile.h"
#include	"TimeMgr.h"
#include	<time.h>


CLFMissile::CLFMissile() : m_pTarg(nullptr)
{
}


CLFMissile::~CLFMissile()
{
}

void CLFMissile::Initialize(void)
{
	m_eItemType = ITEM_BOMB;
	m_tInfo.vSize = { 80, 80, 0 };

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

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;
	}
	else
		m_fCreatedTime += DELTA_TIME;

	

	return 0;
}

void CLFMissile::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;

	if (!m_pTarg || m_pTarg->Get_Dead())
	{
		srand(unsigned(time(NULL)));
	}
}

void CLFMissile::Render(HDC hDC)
{
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
}

void CLFMissile::Release(void)
{
}

void CLFMissile::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_MONSTER)
	{
		m_tInfo.vSize *= 3.f;

		m_fMaxExistTime = 3.f;
	}
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

	D3DXMatrixRotationZ(&mSrc, fAngle * DELTA_TIME);

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mSrc);

}
