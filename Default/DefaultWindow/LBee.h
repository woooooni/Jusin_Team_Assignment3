#pragma once
#include "LItemEffects.h"
class CLBee : public CLItemEffects
{
public:
	CLBee(INFO	p_Info);
	~CLBee();

	// CLItemEffects��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;
};

