#include "stdafx.h"
#include "LMyButton.h"
#include	"KeyMgr.h"
#include	"SceneMgr.h"
#include	"TimeMgr.h"



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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		RECT	myR = {
			m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f,
			m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f,
			m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f,
			m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f

		};

		if (PtInRect(&myR, { (LONG)Get_Mouse().x, (LONG)Get_Mouse().y }))
		{
			m_pOnClick();
		}
	}
	return 0;
}

void CLMyButton::Late_Update(void)
{
}

void CLMyButton::Render(HDC hDC)
{
	Rectangle(hDC,
		(int)(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f),
		(int)(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f),
		(int)(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f)
		);

	if (m_strName != L"")
	{
		RECT	myR = {
			m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f,
			m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f,
			m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f,
			m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f

		};

		DrawText(hDC, m_strName.c_str(), m_strName.length(), &myR, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
}

void CLMyButton::Release(void)
{
}

void CLMyButton::Collide(OBJ_TYPE p_Type, CObj * p_Targ)
{
}
