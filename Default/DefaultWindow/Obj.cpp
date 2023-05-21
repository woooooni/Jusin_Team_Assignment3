#include "stdafx.h"
#include "Obj.h"


CObj::CObj() : m_fSpeed(0.f), m_eObjType(OBJ_END), m_eRendType(REND_OBJECT), m_bDead(false), m_strName(L"")
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CObj::~CObj()
{
}


