#include "stdafx.h"
#include "LItemMgr.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LItem.h"
#include	<time.h>
#include	"TimeMgr.h"


CLItemMgr::CLItemMgr()	:	m_fCreateCoolTime(0.f), m_fLastCreateTime(0.f)
{
}


CLItemMgr::~CLItemMgr()
{
}

void	CLItemMgr::Create_Item()
{
	if (m_fLastCreateTime >= m_fCreateCoolTime)
	{
		INFO	p_Info;


		int		iSrc = rand() % (WINCX - 200);

		int		iTmp = rand() % (WINCY - 200);

		p_Info.vPos = { (float)(100 + iSrc),  (float)(100 + iTmp), 0 };


		iSrc = rand() % 3600;

		MATRIX	mSrc;

		D3DXMatrixRotationZ(&mSrc, D3DXToRadian((float)iSrc * 0.1f));

		p_Info.vDir = { 1, 0, 0 };

		D3DXVec3TransformNormal(&p_Info.vDir, &p_Info.vDir, &mSrc);

		CObjMgr::Get_Inst()->Add_Obj(OBJ_ITEM, CAbstractFactory<CLItem>::Create(p_Info));

		iSrc = rand() % 10;

		m_fCreateCoolTime = ((float)iSrc * 0.1f + 2.f);
		m_fLastCreateTime = 0.f;

	}
	else
		m_fLastCreateTime += DELTA_TIME;

}