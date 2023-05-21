#include "stdafx.h"
#include "LBulletCreator.h"
#include	"TimeMgr.h"
#include	"ObjMgr.h"
#include	"LBullet.h"
#include	"AbstractFactory.h"


CLBulletCreator::CLBulletCreator() : m_fBulletCreateTime(0.2f),m_fBulletCreateCoolTime(0.2f), m_bIsRotateCreator(false)
{
}


CLBulletCreator::~CLBulletCreator()
{
}

void CLBulletCreator::Initialize(void)
{
	m_fMaxExistTime = 3.f;
	m_tInfo.vDir = { 0, 1, 0 };
}

int CLBulletCreator::Update(void)
{
	if (Check_Dead())
		return 1;
	

	if (CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER))
		m_tInfo.vPos = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos;


	if (m_bIsRotateCreator)
	{
		MATRIX mSrc;
		D3DXMatrixRotationZ(&mSrc, D3DXToRadian(360.f * DELTA_TIME * 0.5f));
		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mSrc);
	}
	else if(CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER))
		m_tInfo.vDir = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vDir;
		

	if (m_fBulletCreateTime >= m_fBulletCreateCoolTime)
	{
		CObjMgr::Get_Inst()->Add_Obj(OBJ_EFFECT, CAbstractFactory<CLBullet>::Create(m_tInfo));
		m_fBulletCreateTime = 0.f;
	}

	m_fCreatedTime += DELTA_TIME;
	m_fBulletCreateTime += DELTA_TIME;


	return 0;
}

void CLBulletCreator::Late_Update(void)
{

}

void CLBulletCreator::Render(HDC hDC)
{
}

void CLBulletCreator::Release(void)
{
}

void CLBulletCreator::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
