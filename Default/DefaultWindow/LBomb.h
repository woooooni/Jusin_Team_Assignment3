#pragma once
#include "LItemEffects.h"
class CLBomb : public CLItemEffects
{
public:
	CLBomb();
	~CLBomb();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

private:

	float		m_fSize;

	VECTOR		m_vFLeaf[8];
};

