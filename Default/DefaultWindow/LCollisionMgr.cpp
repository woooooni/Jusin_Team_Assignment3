#include "stdafx.h"
#include "LCollisionMgr.h"


CLCollisionMgr::CLCollisionMgr()
{
}


CLCollisionMgr::~CLCollisionMgr()
{
}

void CLCollisionMgr::Collide(CObj * p_First, CObj * p_Second)
{

	if (p_First->Get_Dead() || p_Second->Get_Dead())
		return;

	const INFO& inF = p_First->Get_Info();
	const INFO& inS = p_Second->Get_Info();

	VECTOR	vSrc = inF.vPos - inS.vPos;

	if (D3DXVec3Length(&vSrc) < (inF.vSize.x + inS.vSize.x) * 0.5f)
	{
		p_First->Collide(p_Second->Get_Type(), p_Second);
		p_Second->Collide(p_First->Get_Type(), p_First);
	}


}
