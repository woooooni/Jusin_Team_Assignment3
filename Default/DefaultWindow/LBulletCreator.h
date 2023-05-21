#pragma once
#include "LItemEffects.h"
class CLBulletCreator :
	public CLItemEffects
{
public:
	CLBulletCreator();
	~CLBulletCreator();

	// CLItemEffects을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

	void	Add_ExistTime() { m_fMaxExistTime += 3.f; }

	void	Set_RotateCreate() { m_bIsRotateCreator = true; m_fBulletCreateCoolTime = 0.1f; }

	bool	Get_RotateCreate() { return m_bIsRotateCreator; }

private:
	float		m_fBulletCreateTime;
	float		m_fBulletCreateCoolTime;


	bool		m_bIsRotateCreator;
};

