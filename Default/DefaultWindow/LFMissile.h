#pragma once
#include "LItemEffects.h"
class CLFMissile : public CLItemEffects
{
public:
	CLFMissile();
	~CLFMissile();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

	void			Set_Target();

private:
	CObj*		m_pTarg;

	void			Follow_Target();

	VECTOR		m_vSubCircleCenter;
	float		m_vSubCircleRad;
		
};

