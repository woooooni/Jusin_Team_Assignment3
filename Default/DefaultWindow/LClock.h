#pragma once
#include "LUIBase.h"
class CLClock :
	public CLUIBase
{
public:
	CLClock();
	~CLClock();

	// CLUIBase을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

private:

	TCHAR	m_strTmp[32];
	float	m_fCurTime;
};

