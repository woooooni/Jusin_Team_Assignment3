#pragma once
#include "LItemEffects.h"
class CLBullet :
	public CLItemEffects
{
public:
	CLBullet(INFO p_Info);
	~CLBullet();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

private:
	D3DXVECTOR3		m_vLineP[3];

	VECTOR			m_vEyePos[2];
	VECTOR			m_vEyeDongjaPos[2];
	float			m_fEyeSize;
	float			m_fDongjaSize;

};

