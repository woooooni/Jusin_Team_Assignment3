#include "stdafx.h"
#include "LMonsterMgr.h"
#include	"TimeMgr.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LMonster.h"
#include	<time.h>

CLMonsterMgr*	CLMonsterMgr::inst = nullptr;

CLMonsterMgr::CLMonsterMgr()	:	m_fLastCreateTime(0.f), m_fCreateCoolTime(3.f)
{
}


CLMonsterMgr::~CLMonsterMgr()
{
}

void CLMonsterMgr::Create_Monster()
{
	if (!CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER))
		return;

	if (m_fLastCreateTime < m_fCreateCoolTime)
	{
		m_fLastCreateTime += DELTA_TIME;

	}
	else
	{
		INFO	p_Info;

		ZeroMemory(&p_Info, sizeof(INFO));

		p_Info.vPos = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos;

		VECTOR vSrc = { 1,0,0 };
		MATRIX	mWorld;
		MATRIX	mSrc;

		srand(unsigned(time(NULL)));


		int		iSrc = rand() % 200;

		D3DXMatrixScaling(&mSrc, (FLOAT)(100 + iSrc), 0, 0);
		mWorld *= mSrc;

		iSrc = rand() % 360;

		D3DXMatrixRotationZ(&mSrc, D3DXToRadian(iSrc));
		mWorld *= mSrc;

		D3DXVec3TransformCoord(&vSrc, &vSrc, &mWorld);

		p_Info.vPos += vSrc;

		p_Info.vDir = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos - p_Info.vPos;

		D3DXVec3Normalize(&p_Info.vDir, &p_Info.vDir);

		CObjMgr::Get_Inst()->Add_Obj(OBJ_MONSTER, CAbstractFactory<CLMonster>::Create(p_Info));

		m_fLastCreateTime = 0.f;

		if (m_fCreateCoolTime > 0.5f)
			m_fCreateCoolTime -= 0.05f;
		else
			m_fCreateCoolTime = 1.f;
	}
}
