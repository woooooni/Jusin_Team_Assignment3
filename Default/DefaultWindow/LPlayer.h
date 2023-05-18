#pragma once
#include "Obj.h"
class CLPlayer : public CObj
{
public:
	CLPlayer();
	virtual ~CLPlayer();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Key_Input(void);

	D3DXVECTOR3		m_vLineP[3];




	// CObj��(��) ���� ��ӵ�
	virtual void Collide(OBJ_TYPE p_type, CObj * p_targ) override;

};
