#include "stdafx.h"
#include "LCamMgr.h"


CLCamMgr::CLCamMgr() : m_vCampos({WINCX * 0.5f, WINCY * 0.5f, 0}), m_fScale(1.f)
{
}


CLCamMgr::~CLCamMgr()
{
}

VECTOR CLCamMgr::Get_ScreenPos(const VECTOR & p_V)
{
	VECTOR	v_Src = p_V - m_vCampos;

	v_Src *= m_fScale;

	v_Src += {WINCX * 0.5f, WINCY * 0.5f, 0};

	return v_Src;
}
