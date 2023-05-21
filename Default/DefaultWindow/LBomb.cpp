#include "stdafx.h"
#include "LBomb.h"
#include	"ObjMgr.h"
#include	"TimeMgr.h"


CLBomb::CLBomb()
{
}


CLBomb::~CLBomb()
{
}

void CLBomb::Initialize(void)
{
	m_eItemType = ITEM_BOMB;
	m_tInfo.vSize = { 250, 250, 0 };
	m_tInfo.vDir = { 1, 0, 0 };

	m_fCreatedTime = 0.f;
	m_fMaxExistTime = 3.f;
	m_fSize = 0.f;

	VECTOR	vSrc = { 125.f, 0, 0 };

	MATRIX mat;

	D3DXMatrixRotationZ(&mat, D3DXToRadian(45.f));


	for (size_t i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&vSrc, &vSrc, &mat);

		m_vFLeaf[i] = vSrc;
	}

					
}

int CLBomb::Update(void)
{
	m_fCreatedTime += DELTA_TIME;

	if (m_fCreatedTime <= 0.5f)
		m_fSize += DELTA_TIME * (1.f / 0.5f);
	else if (m_fCreatedTime > 2.5f)
		m_fSize += DELTA_TIME * (-1.f / 0.5f);

	MATRIX mat;

	D3DXMatrixRotationZ(&mat, D3DXToRadian(90 * DELTA_TIME));

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mat);

	Check_Dead();

	return 0;
}

void CLBomb::Late_Update(void)
{
}

void CLBomb::Render(HDC hDC)
{
	HBRUSH myB = CreateSolidBrush(RGB(255, 0, 50));
	HBRUSH oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y * m_fSize * 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);

	MATRIX		mWorld, mSize, mRot, mTrans;

	D3DXMatrixScaling(&mSize, m_fSize, m_fSize, 0);

	float	fAngle = m_tInfo.vDir.y > 0 ? acosf(m_tInfo.vDir.x) : -acosf(m_tInfo.vDir.x);

	D3DXMatrixRotationZ(&mRot, fAngle);

	D3DXMatrixTranslation(&mTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	mWorld = mSize * mRot * mTrans;

	VECTOR	vec;

	HPEN myPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 150));

	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);


	for (size_t i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&vec, &m_vFLeaf[i], &mWorld);

		MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);

		LineTo(hDC, vec.x, vec.y);
	}

	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	myB = CreateSolidBrush(RGB(255, 255, 150));
	oldB = (HBRUSH)SelectObject(hDC, myB);

	Ellipse(hDC,
		(int)(m_tInfo.vPos.x - 50 * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.y - 50 * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.x + 50 * m_fSize * 0.5f),
		(int)(m_tInfo.vPos.y + 50 * m_fSize * 0.5f)
		);

	SelectObject(hDC, oldB);
	DeleteObject(myB);
}

void CLBomb::Release(void)
{
}

void CLBomb::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
