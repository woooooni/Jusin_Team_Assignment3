#include "stdafx.h"
#include "LItemEffects.h"


CLItemEffects::CLItemEffects() : m_fCreatedTime(0.f), m_fMaxExistTime(0.f), m_eItemType(ITEM_END)
{
	m_eRendType = REND_BACKGROUND;
	m_eObjType = OBJ_EFFECT;
}


CLItemEffects::~CLItemEffects()
{
}

bool CLItemEffects::Check_Dead()
{
	if (m_fMaxExistTime != 0.f && m_fCreatedTime >= m_fMaxExistTime)
	{
		m_bDead = true;
		return true;
	}
	else
		return false;
}
