#include "stdafx.h"
#include "LMonster.h"
#include	"ObjMgr.h"
#include	"TimeMgr.h"
#include	"LCamMgr.h"

CLMonster::CLMonster(INFO	p_Info) : m_bTargetd(false)
{
	m_tInfo = p_Info;
}


CLMonster::~CLMonster()
{
}

void CLMonster::Initialize(void)
{
	m_tInfo.vSize = { 50.f, 50.f, 0.f };

	m_eObjType = OBJ_MONSTER;

	m_fEyeSize = 17.f;
	m_fDongjaSize = 10.f;

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

int CLMonster::Update(void)
{

	if (m_tInfo.vPos.x < -100.f || m_tInfo.vPos.x > WINCX + 100.f || m_tInfo.vPos.y < -100.f || m_tInfo.vPos.y > WINCY + 100.f)
	{
		m_bDead = true;
		return 1;
	}

	//Follow_Player();

	m_fSpeed = 100.f * DELTA_TIME;

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	return 0;
}

void CLMonster::Late_Update(void)
{
}

void CLMonster::Render(HDC hDC)
{

	HBRUSH myB = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	VECTOR vSrc = CLCamMgr::GetInst()->Get_ScreenPos(m_tInfo.vPos);

	Ellipse(hDC,
		(int)(vSrc.x - m_tInfo.vSize.x * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
		(int)(vSrc.y - m_tInfo.vSize.y * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
		(int)(vSrc.x + m_tInfo.vSize.x * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
		(int)(vSrc.y + m_tInfo.vSize.y * 0.5f * CLCamMgr::GetInst()->Get_Scale())
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);

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


		HBRUSH myB = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);


		Ellipse(hDC,
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x - m_fEyeSize * 0.5f * CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y - m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).x + m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale()),
			(int)(CLCamMgr::GetInst()->Get_ScreenPos(vSrc).y + m_fEyeSize* 0.5f* CLCamMgr::GetInst()->Get_Scale())
			);

		SelectObject(hDC, oldB);
		DeleteObject(myB);



	}

}

void CLMonster::Release(void)
{
}

void CLMonster::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	if (p_Type == OBJ_EFFECT)
		m_bDead = true;
}

void CLMonster::Follow_Player()
{
	CObj* player = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER);

	if (player == nullptr)
		return;

	m_tInfo.vDir = player->Get_Info().vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

}
