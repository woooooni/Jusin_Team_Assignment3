#include "stdafx.h"
#include "Ground_TW.h"
#include "Camera_TW.h"

CGround_TW::CGround_TW()
	:CObj_TW(OBJ_TYPE::OBJ_GROUND)
{
}


CGround_TW::~CGround_TW()
{
}

void CGround_TW::Initialize(void)
{
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });

	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
		m_vecVertices.push_back(m_vecOriginVertices[i]);

	ChangeState(STATE::IDLE);
}

int CGround_TW::Update(void)
{
	ResetVertices();

	D3DXMATRIX matScale, matRotZ, matTrans;

	float fMagnification = CCamera_TW::GetInst()->GetMagnification();
	D3DXMatrixScaling(&matScale, 1.f * fMagnification, 1.f * fMagnification, 1.f * fMagnification);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x / fMagnification , m_vPos.y / fMagnification, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	return 0;
}

void CGround_TW::Late_Update(void)
{

}

void CGround_TW::Render(HDC hDC)
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	MoveToEx(hDC, (int)vRenderPos.x, (int)vRenderPos.y, nullptr);

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
	{
		vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[i]);
		LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);
	}

	vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);

}

void CGround_TW::Release(void)
{

}

void CGround_TW::Update_Idle()
{
}

void CGround_TW::Update_Move()
{
}

void CGround_TW::Update_Jump()
{
}

void CGround_TW::Update_Hang()
{
}

void CGround_TW::Update_Die()
{
}

void CGround_TW::Update_TimeRewind()
{
}

void CGround_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	
}

