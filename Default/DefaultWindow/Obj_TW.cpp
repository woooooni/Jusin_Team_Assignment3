#include "stdafx.h"
#include "Obj_TW.h"
#include "ObjMgr.h"


CObj_TW::CObj_TW(OBJ_TYPE _eType)
	: m_eObjType(_eType)
	, m_bGround(false)
	, m_fAngle(0.f)
{

}

CObj_TW::~CObj_TW()
{

}

void CObj_TW::Initialize(void)
{

}

int CObj_TW::Update(void)
{
	return 0;
}

void CObj_TW::Late_Update(void)
{

}

void CObj_TW::Render(HDC hDC)
{

}

void CObj_TW::Release(void)
{
	
}

void CObj_TW::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
	// No Use
}

void CObj_TW::ResetVertices()
{
	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
	{
		m_vecVertices[i] = m_vecOriginVertices[i];
	}
}
