#pragma once
#include "Obj.h"
class CJItem_Ball :
	public CObj
{
public:
	CJItem_Ball();
	virtual ~CJItem_Ball();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

private:
	vector<D3DXVECTOR3>		m_vecSavePoint;
	D3DXVECTOR3				m_vSaveDir;

	D3DXMATRIX	m_matWorld;
	D3DXMATRIX	m_matScale;
	D3DXMATRIX	m_matRot;
	D3DXMATRIX	m_matTrans;

	float		m_fAngle;
};

