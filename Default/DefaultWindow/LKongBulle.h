#pragma once
#include "LItemEffects.h"
class CLKongBulle : public CLItemEffects
{
public:
	CLKongBulle();
	~CLKongBulle();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;


private:

	VECTOR			m_vEyePos, m_vEyeDongjaPos, m_vLook;

	float		m_fEyeSize, m_fDongjaSize;

	VECTOR		m_vLines[6];
					
};

