#pragma once
#include "LItemEffects.h"
class CLCosmos : public CLItemEffects
{
public:
	CLCosmos();
	~CLCosmos();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;


private:
	VECTOR		m_vCosmosPos[8];
	CObj*		m_pCosmos[8];
};

