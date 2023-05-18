#include "stdafx.h"
#include "LMyButton.h"


CLMyButton::CLMyButton(INFO	p_Info)	: m_pOnClick(nullptr)
{
	m_tInfo = p_Info;
}


CLMyButton::~CLMyButton()
{
}

void CLMyButton::Initialize(void)
{
}

int CLMyButton::Update(void)
{
	return 0;
}

void CLMyButton::Late_Update(void)
{
}

void CLMyButton::Render(HDC hDC)
{
}

void CLMyButton::Release(void)
{
}

void CLMyButton::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
