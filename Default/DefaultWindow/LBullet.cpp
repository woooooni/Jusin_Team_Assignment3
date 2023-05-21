#include "stdafx.h"
#include "LBullet.h"
#include	"TimeMgr.h"
#include	"LCamMgr.h"

CLBullet::CLBullet(INFO p_Info)
{
	m_tInfo = p_Info;
}


CLBullet::~CLBullet()
{
}

void CLBullet::Initialize(void)
{
	m_tInfo.vSize = { 25, 25, 0 };
	m_fSpeed = 200.f;

	m_vLineP[0] = { cosf(D3DXToRadian(75.f)) * m_tInfo.vSize.x * 0.5f, sinf(D3DXToRadian(75.f)) * m_tInfo.vSize.y* 0.5f ,0 };
	m_vLineP[1] = { cosf(D3DXToRadian(75.f)) * m_tInfo.vSize.x* 0.5f, -sinf(D3DXToRadian(75.f)) * m_tInfo.vSize.y* 0.5f ,0 };
	m_vLineP[2] = { -m_tInfo.vSize.x* 0.5f, 0,0 };

	m_fEyeSize = 9.f;
	m_fDongjaSize = 5.f;

	VECTOR		vSrc = { (m_tInfo.vSize.x - m_fEyeSize) * 0.5f, 0, 0 };

	MATRIX		mSrc;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(30.f));

	D3DXVec3TransformCoord(&m_vEyePos[0], &vSrc, &mSrc);

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(-30.f));

	D3DXVec3TransformCoord(&m_vEyePos[1], &vSrc, &mSrc);

	VECTOR		vTmp = { (m_fEyeSize - m_fDongjaSize) * 0.5f, 0,0 };

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(-10.f));

	D3DXVec3TransformCoord(&vTmp, &vTmp, &mSrc);

	m_vEyeDongjaPos[0] = m_vEyePos[0] + vTmp;

	D3DXMatrixRotationZ(&mSrc, D3DXToRadian(20.f));

	D3DXVec3TransformCoord(&vTmp, &vTmp, &mSrc);

	m_vEyeDongjaPos[1] = m_vEyePos[1] + vTmp;


}

int CLBullet::Update(void)
{

	if (m_tInfo.vPos.x < -100.f || m_tInfo.vPos.x > WINCX + 100.f || m_tInfo.vPos.y < -100.f || m_tInfo.vPos.y > WINCY + 100.f)
	{
		m_bDead = true;
		return 1;
	}


	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * DELTA_TIME;

	return 0;
}

void CLBullet::Late_Update(void)
{
	if (m_bDead)
		m_eRendType = REND_END;
}

void CLBullet::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 155, 155));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);

	vector<D3DXVECTOR3> vecSrc;

	D3DXMATRIX mSrc;
	for (size_t i = 0; i < 3; i++)
	{
		vecSrc.push_back(m_vLineP[i]);



		float fAngle = acosf(m_tInfo.vDir.x);

		if (m_tInfo.vDir.y < 0)
			fAngle = 2.f * PI - fAngle;

		D3DXMatrixRotationZ(&mSrc, fAngle);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

		D3DXMatrixTranslation(&mSrc, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

	}


	MoveToEx(hDC, (int)vecSrc[0].x, (int)vecSrc[0].y, nullptr);
	LineTo(hDC, (int)vecSrc[1].x, (int)vecSrc[1].y);

	D3DXVECTOR3		vSrc = vecSrc[0] + ((vecSrc[1] - vecSrc[0]) * 0.5f);

	MoveToEx(hDC, (int)vSrc.x, (int)vSrc.y, nullptr);
	LineTo(hDC, (int)vecSrc[2].x, (int)vecSrc[2].y);

	for (size_t i = 0; i < 2; i++)
	{
		MATRIX		matWorld, matRot, matTrans;

		float fAngle = acosf(m_tInfo.vDir.x);

		if (m_tInfo.vDir.y < 0)
			fAngle = 2.f * PI - fAngle;

		D3DXMatrixRotationZ(&matRot, fAngle);
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

		matWorld = matRot * matTrans;

		VECTOR	vSrc;

		D3DXVec3TransformCoord(&vSrc, &m_vEyePos[i], &matWorld);

		Ellipse(hDC,
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x - m_fEyeSize * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y - m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x + m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y + m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale())
			);

		D3DXVec3TransformCoord(&vSrc, &m_vEyeDongjaPos[i], &matWorld);

		HBRUSH myB = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

		Ellipse(hDC,
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x - m_fDongjaSize * 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y - m_fDongjaSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x + m_fDongjaSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y + m_fDongjaSize* 0.5f* CLCamMgr::GetInst()->Get_Scale())
			);

		SelectObject(hDC, oldB);
		DeleteObject(myB);


	}


}

void CLBullet::Release(void)
{
}

void CLBullet::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
