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

	void			Set_Target(CObj*  p_Target)
	{
		m_pTarg = p_Target;

		m_tInfo.vDir = p_Target->Get_Info().vPos - m_tInfo.vPos;

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		MATRIX		mSrc;

		D3DXMatrixRotationZ(&mSrc, D3DXToRadian(30.f));

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &mSrc);

	}

private:
	CObj*		m_pTarg;

	void			Follow_Target();
		
};

