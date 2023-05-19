#pragma once
#include "Obj.h"
#include	"DefineL.h"
class CLItemEffects :
	public CObj
{
public:
	CLItemEffects();
	virtual ~CLItemEffects();


protected:
	LITEM_TYPE		m_eItemType;
	float			m_fCreatedTime;
	float			m_fMaxExistTime;

	bool			Check_Dead();
};

