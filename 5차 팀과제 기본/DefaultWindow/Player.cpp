#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { {400.f, 300.f,0.f},{1.f,0.f,0.f} ,{100.f, 100.f,0.f} };
	m_fSpeed = 10.f;
	
}

int CPlayer::Update(void)
{



	return 0;
}

void CPlayer::Render(HDC hDC)
{
}

void CPlayer::Release(void)
{
}

void CPlayer::Key_Input(void)
{


}

void CPlayer::Late_Update(void)
{
}
