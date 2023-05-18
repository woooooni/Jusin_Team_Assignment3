#pragma once
#include "LUIBase.h"
class CLMyButton : public CLUIBase
{
public:
	CLMyButton(INFO	p_Info);
	virtual ~CLMyButton();

	// CLUIBase을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

	void			Set_ClickEvent(void(*p_Ev)()) {
		m_pOnClick = p_Ev;
	}

private:
	void(*m_pOnClick)();
};

