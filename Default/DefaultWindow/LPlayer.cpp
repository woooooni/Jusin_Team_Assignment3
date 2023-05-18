#include "stdafx.h"
#include "LPlayer.h"



CLPlayer::CLPlayer()
{
}


CLPlayer::~CLPlayer()
{
	Release();
}

void CLPlayer::Initialize(void)
{
	m_tInfo = { { 400.f, 300.f,0.f },{ 1.f,0.f,0.f } ,{ 100.f, 100.f,0.f } };
	m_fSpeed = 3.f;
	m_eObjType = OBJ_PLAYER;

	m_vLineP[0] = { cosf(D3DXToRadian(75.f)) * 50.f, sinf(D3DXToRadian(75.f)) * 50.f ,0 };
	m_vLineP[1] = { cosf(D3DXToRadian(75.f)) * 50.f, -sinf(D3DXToRadian(75.f)) * 50.f ,0 };
	m_vLineP[2] = { -50.f, 0,0 };


}

int CLPlayer::Update(void)
{
	Key_Input();


	return 0;
}

void CLPlayer::Render(HDC hDC)
{

	HBRUSH myB = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f,
		m_tInfo.vPos.y - m_tInfo.vSize.y* 0.5f,
		m_tInfo.vPos.x + m_tInfo.vSize.x* 0.5f,
		m_tInfo.vPos.y + m_tInfo.vSize.y* 0.5f
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);



	vector<D3DXVECTOR3> vecSrc;

	D3DXMATRIX mSrc;
	for (size_t i = 0; i < 3; i++)
	{
		vecSrc.push_back(m_vLineP[i]);

		float fc = D3DXVec3Dot(&D3DXVECTOR3(1, 0, 0), &m_tInfo.vDir);

		float fAngle = acosf(fc);

		if (m_tInfo.vDir.y < 0)
			fAngle = 2 * PI - fAngle;

		D3DXMatrixRotationZ(&mSrc, fAngle);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

		D3DXMatrixTranslation(&mSrc, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);

		D3DXVec3TransformCoord(&vecSrc[i], &vecSrc[i], &mSrc);

	}


	MoveToEx(hDC, vecSrc[0].x, vecSrc[0].y, nullptr);
	LineTo(hDC, vecSrc[1].x, vecSrc[1].y);

	D3DXVECTOR3		vSrc = vecSrc[0] + ((vecSrc[1] - vecSrc[0]) * 0.5f);

	MoveToEx(hDC, vSrc.x, vSrc.y, nullptr);
	LineTo(hDC, vecSrc[2].x, vecSrc[2].y);

}

void CLPlayer::Release(void)
{
}

void CLPlayer::Key_Input(void)
{



	D3DXVECTOR3 vTmp = ::Get_Mouse() - m_tInfo.vPos;

	D3DXVec3Normalize(&vTmp, &vTmp);

	m_tInfo.vDir = vTmp;



	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

}

void CLPlayer::Collide(OBJ_TYPE p_type, CObj * p_targ)
{
}

void CLPlayer::Late_Update(void)
{
}
