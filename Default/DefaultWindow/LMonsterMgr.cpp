#include "stdafx.h"
#include "LMonsterMgr.h"
#include	"TimeMgr.h"
#include	"ObjMgr.h"
#include	"AbstractFactory.h"
#include	"LMonster.h"
#include	<time.h>
#include	<algorithm>
#include	"LDecoy.h"

CLMonsterMgr*	CLMonsterMgr::inst = nullptr;

CLMonsterMgr::CLMonsterMgr()	:	m_fLastCreateTime(0.f), m_fCreateCoolTime(2.f), m_fLevel(1.f)
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
		m_fLevel += DELTA_TIME * 0.1f;

	}
	else
	{
		int iTmp = rand() % 2;

		for (int i = 0; i < (int)m_fLevel + iTmp; i++)
		{

			INFO	p_Info;

			ZeroMemory(&p_Info, sizeof(INFO));



			p_Info.vPos = {WINCX * 0.5f, WINCY * 0.5f, 0};

			VECTOR vSrc = { WINCX * 0.5f + 50.f,0,0 };
			MATRIX	mSrc;

			int iSrc = rand() % 3600;

			if (iSrc > 450 && iSrc < 1350)
				iSrc += 1800;


			D3DXMatrixRotationZ(&mSrc, D3DXToRadian((float)iSrc * 0.1f));
			

			D3DXVec3TransformCoord(&vSrc, &vSrc, &mSrc);


			if (vSrc.y > WINCY * 0.5f + 25.f)
				vSrc.y = WINCY * 0.5f + 25.f;
			if (vSrc.y < -WINCY * 0.5f -25.f)
				vSrc.y = -WINCY * 0.5f -25.f;

			p_Info.vPos += vSrc;

	

			if (!CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT).empty())
			{
				auto iter = find_if(CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT).begin(), CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT).end(), [&](auto iter)->bool
				{
					return dynamic_cast<CLDecoy*>(iter);
				}
				);

				if (iter == CObjMgr::Get_Inst()->Get_All(OBJ_EFFECT).end())
				{
					p_Info.vDir = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos - p_Info.vPos;

				}
				else
				{
					p_Info.vDir = (*iter)->Get_Info().vPos - p_Info.vPos;
				}
			}
			else
			{
				p_Info.vDir = CObjMgr::Get_Inst()->Get_Last(OBJ_PLAYER)->Get_Info().vPos - p_Info.vPos;

			}


			D3DXVec3Normalize(&p_Info.vDir, &p_Info.vDir);

			CObjMgr::Get_Inst()->Add_Obj(OBJ_MONSTER, CAbstractFactory<CLMonster>::Create(p_Info));
		}

		auto src = CObjMgr::Get_Inst()->Get_All(OBJ_MONSTER);



		m_fLastCreateTime = 0.f;

		if (m_fCreateCoolTime > 0.5f)
			m_fCreateCoolTime -= 0.05f;
		else
			m_fCreateCoolTime = 0.5f;
	}
}
