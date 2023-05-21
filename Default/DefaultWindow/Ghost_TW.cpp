#include "stdafx.h"
#include "Ghost_TW.h"
#include "Camera_TW.h"

CGhost_TW::CGhost_TW()
	:CObj_TW(OBJ_TYPE::OBJ_GHOST)
{

}


CGhost_TW::~CGhost_TW()
{
}

void CGhost_TW::Initialize(void)
{
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });
	m_vecOriginVertices.push_back(D3DXVECTOR3{ -m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f });

	for (UINT i = 0; i < m_vecOriginVertices.size(); ++i)
		m_vecVertices.push_back(m_vecOriginVertices[i]);

	ChangeState(STATE::IDLE);
}

int CGhost_TW::Update(void)
{
	if (!m_timeStampList.empty())
	{
		m_vPos = m_timeStampList.front().vPos;
		m_fAngle = m_timeStampList.front().fAngle;
		m_timeStampList.pop_front();
	}
	ResetVertices();

	D3DXMATRIX matScale, matRotZ, matTrans;

	float fMagnification = CCamera_TW::GetInst()->GetMagnification();
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, 0.f);

	m_matWorld = matScale * matRotZ * matTrans;

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i], &m_vecOriginVertices[i], &m_matWorld);

	return 0;
}

void CGhost_TW::Late_Update(void)
{
	CObj_TW::Late_Update();
}

void CGhost_TW::Render(HDC hDC)
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

void CGhost_TW::Release(void)
{

}

void CGhost_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
}

void CGhost_TW::Update_Idle()
{

}

void CGhost_TW::Update_Move()
{
}

void CGhost_TW::Update_Jump()
{
}

void CGhost_TW::Update_Hang()
{
}

void CGhost_TW::Update_Die()
{
}

void CGhost_TW::Update_TimeRewind()
{
}

