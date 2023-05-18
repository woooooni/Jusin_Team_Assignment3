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

}

int CGround_TW::Update(void)
{
	return 0;
}

void CGround_TW::Late_Update(void)
{

}

void CGround_TW::Render(HDC hDC)
{
	D3DXVECTOR3 vRenderPos = CCamera_TW::GetInst()->GetRenderPos(m_vPos);

	Rectangle(hDC,
		int(vRenderPos.x - GetScale().x / 2.f),
		int(vRenderPos.y - GetScale().y / 2.f),
		int(vRenderPos.x + GetScale().x / 2.f),
		int(vRenderPos.y + GetScale().y / 2.f));
}

void CGround_TW::Release(void)
{

}


void CGround_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
	
}

