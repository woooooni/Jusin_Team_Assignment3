#include "stdafx.h"
#include "LKongBulle.h"
#include	"TimeMgr.h"
#include	"ObjMgr.h"


CLKongBulle::CLKongBulle()
{
}


CLKongBulle::~CLKongBulle()
{
}

void CLKongBulle::Initialize(void)
{
	m_tInfo = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info();

	m_tInfo.vSize = { 150,150,0 };

	m_vLook = { 1,0,0 };

	m_fMaxExistTime = 7.f;

	m_vEyePos = { 50, 0, 0 };

	MATRIX	mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(-35.f));

	D3DXVec3TransformCoord(&m_vEyePos, &m_vEyePos, &mSrc);

	m_fEyeSize = 50.f;

	m_vEyeDongjaPos = m_vEyePos + VECTOR({14, 0, 0});

	m_fDongjaSize = 22.f;


	m_fSpeed = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Speed();

	VECTOR		vSrc = { 75, 0,0 };

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian( 45.f));


	for (size_t i = 0; i < 6; i++)
	{
		m_vLines[i] = vSrc;

		D3DXVec3TransformCoord(&vSrc, &vSrc, &mSrc);
	}

}

int CLKongBulle::Update(void)
{
	if (Check_Dead())
		return 1;

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

	m_fCreatedTime += DELTA_TIME;

	MATRIX mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(m_fSpeed * (180.f / 300.f) * DELTA_TIME));

	D3DXVec3TransformNormal(&m_vLook, &m_vLook, &mSrc);

	return 0;
}

void CLKongBulle::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLKongBulle::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(155, 50, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);

	MATRIX matW, matR, matT;

	float fAngle = m_vLook.y >= 0 ? acosf(m_vLook.x) : -acosf(m_vLook.x);

	D3DXMatrixRotationZ(&matR, fAngle);

	D3DXMatrixTranslation(&matT, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

	matW = matR * matT;

	VECTOR vSrc;

	D3DXVec3TransformCoord(&vSrc, &m_vEyePos, &matW);

	Ellipse(hDC,
		(int)(vSrc.x - m_fEyeSize * 0.5f),
		(int)(vSrc.y - m_fEyeSize * 0.5f),
		(int)(vSrc.x + m_fEyeSize * 0.5f),
		(int)(vSrc.y + m_fEyeSize * 0.5f)
		);

	 myB = CreateSolidBrush(RGB(0, 0, 0));
	 oldB = (HBRUSH)SelectObject(hDC, myB);

	D3DXVec3TransformCoord(&vSrc, &m_vEyeDongjaPos, &matW);

	Ellipse(hDC,
		(int)(vSrc.x - m_fDongjaSize * 0.5f),
		(int)(vSrc.y - m_fDongjaSize * 0.5f),
		(int)(vSrc.x + m_fDongjaSize * 0.5f),
		(int)(vSrc.y + m_fDongjaSize * 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);


	MATRIX		mWorld,mRot, mTrans;

	D3DXMatrixRotationZ(&mRot, fAngle);

	D3DXMatrixTranslation(&mTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	mWorld =  mRot * mTrans;

	VECTOR	vec;

	HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 205, 155));

	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);


	for (size_t i = 0; i < 6; i++)
	{
		D3DXVec3TransformCoord(&vec, &m_vLines[i], &mWorld);

		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

		LineTo(hDC, vec.x, vec.y);
	}

	SelectObject(hDC, oldPen);
	DeleteObject(myPen);




}

void CLKongBulle::Release(void)
{
}

void CLKongBulle::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
