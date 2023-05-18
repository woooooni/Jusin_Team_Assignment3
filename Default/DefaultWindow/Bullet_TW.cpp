#include "stdafx.h"
#include "Bullet_TW.h"


CBullet_TW::CBullet_TW()
	:CObj_TW(OBJ_TYPE::OBJ_BULLET)
{

}


CBullet_TW::~CBullet_TW()
{
}

void CBullet_TW::Initialize(void)
{
}

int CBullet_TW::Update(void)
{
	return 0;
}

void CBullet_TW::Late_Update(void)
{
}

void CBullet_TW::Render(HDC hDC)
{
}

void CBullet_TW::Release(void)
{
}

void CBullet_TW::OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther)
{
}
