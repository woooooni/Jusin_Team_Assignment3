#include "stdafx.h"
#include "Ghost_TW.h"
#include "Camera_TW.h"

CGhost_TW::CGhost_TW()
	:CObj_TW(OBJ_TYPE::OBJ_GHOST)
	, m_pOwner(nullptr)
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

	ChangeState(STATE::JUMP);
}

int CGhost_TW::Update(void)
{
	if (m_pOwner->GetState() != STATE::TIME_REWIND)
		Record();

	if (m_eState != STATE::IDLE)
		return 0;
	
	switch (m_eState)
	{
	case STATE::IDLE:
		Update_Idle();
		break;
	case STATE::MOVE:
		Update_Move();
		break;
	case STATE::HANG:
		Update_Hang();
		break;
	case STATE::JUMP:
		Update_Jump();
		break;
	case STATE::TIME_REWIND:
		Update_TimeRewind();
		break;
	case STATE::DIE:
		Update_Die();
		break;
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
	if (m_eState != STATE::IDLE)
		return;

	CObj_TW::Late_Update();
	
}

void CGhost_TW::Render(HDC hDC)
{
	if (m_eState != STATE::IDLE)
		return;

	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(66, 0, 99));
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	MoveToEx(hDC, (int)vRenderPos.x, (int)vRenderPos.y, nullptr);

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
	{
		vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[i]);
		LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);
	}

	vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vecVertices[0]);
	LineTo(hDC, (int)vRenderPos.x, (int)vRenderPos.y);


	wstring strNameTag = L"Ghost";
	TextOut(hDC, (int)vRenderPos.x - strNameTag.size(), int(vRenderPos.y - GetScale().y / 2.f - 20), strNameTag.c_str(), strNameTag.size());

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

void CGhost_TW::Release(void)
{

}

void CGhost_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
}

void CGhost_TW::Update_Idle()
{
	if (!m_recordingList.empty())
	{
		m_vPos = m_recordingList.front().vPos;
		m_fAngle = m_recordingList.front().fAngle;
		m_recordingList.pop_front();
	}
	else
	{
		ChangeState(STATE::JUMP);
	}
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

void CGhost_TW::Record()
{
	TIME_STAMP tStamp;
	tStamp.vPos = m_pOwner->GetPos();
	tStamp.vScale = m_pOwner->GetScale();
	tStamp.fAngle = m_pOwner->GetAngle();
	tStamp.bActive = m_pOwner->IsActive();

	m_realTimeList.push_back(tStamp);

	
}

void CGhost_TW::Play()
{
	m_recordingList.clear();
	m_recordingList = m_realTimeList;
	m_realTimeList.clear();
	ChangeState(STATE::IDLE);
}

