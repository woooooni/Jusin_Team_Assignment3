#pragma once
#include "Obj.h"
class CLMonster : public CObj
{
public:
	CLMonster(INFO	p_Info);
	virtual ~CLMonster();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

	void		Set_Targetd() { m_bTargetd = true; }
	bool		Get_Targetd() {
		return m_bTargetd
			;
	}

protected:


	bool		m_bTargetd;
	void		Follow_Player();
};

