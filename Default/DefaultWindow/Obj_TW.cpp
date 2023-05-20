#include "stdafx.h"
#include "Obj_TW.h"
#include "ObjMgr.h"
#include "Camera_TW.h"
#include "TimeMgr.h"

CObj_TW::CObj_TW(OBJ_TYPE _eType)
	: m_eObjType(_eType)
	, m_bGround(false)
	, m_fAngle(0.f)
	, m_bActive(true)
	, m_bDelete(false)
	, m_eState(STATE::END)
	, m_fAccTimeStamp(0.f)
	, m_fTimeStampDelay(0.005f)
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
	D3DXMATRIX		matScale, matBackTrans, matOriginTrans, matNewWorld;
	float fMag = CCamera_TW::GetInst()->GetMagnification();

	D3DXVECTOR3	vPlayerPos = CCamera_TW::GetInst()->GetTargetObj()->GetPos();
	D3DXMatrixTranslation(&matBackTrans, -vPlayerPos.x, -vPlayerPos.y, 0.f);
	D3DXMatrixTranslation(&matOriginTrans, vPlayerPos.x, vPlayerPos.y, 0.f);
	D3DXMatrixScaling(&matScale, 1.f * fMag, 1.f * fMag, 1.f);

	matNewWorld = matBackTrans * matScale * matOriginTrans;
	for (UINT i = 0; i < m_vecVertices.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecVertices[i], &matBackTrans);
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecVertices[i], &matScale);
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecVertices[i], &matOriginTrans);
	}
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
	m_fAccTimeStamp += DELTA_TIME;
	if (m_fAccTimeStamp >= m_fTimeStampDelay)
	{
		m_stackTimeStamp.push({ m_vPos, m_vScale, m_fAngle, IsActive() });
		m_fAccTimeStamp = 0.f;
	}
	
}

void CObj_TW::ChangeState(STATE _eState)
{
	if (m_eState == _eState)
		return;

	m_eState = _eState;
}
