#include "stdafx.h"
#include "Obj_TW.h"
#include "ObjMgr.h"


CObj_TW::CObj_TW(OBJ_TYPE _eType)
	: m_eObjType(_eType)
	, m_bGround(false)
	, m_fAngle(0.f)
	, m_bActive(true)
	, m_bDelete(false)
	, m_eState(STATE::END)
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

void CObj_TW::Update_TimeStamp()
{
	m_stackTimeStamp.push({ m_vPos, m_vScale, m_fAngle, IsActive() });
}

void CObj_TW::ChangeState(STATE _eState)
{
	if (m_eState == _eState)
		return;

	m_eState = _eState;
}
