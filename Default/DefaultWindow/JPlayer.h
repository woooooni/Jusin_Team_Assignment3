#pragma once
#include "Obj.h"
class CJPlayer :
	public CObj
{
public:
	CJPlayer();
	virtual ~CJPlayer();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

public:
	void	Set_Size(float _fTemp) { m_tInfo.vSize.x += _fTemp; }

	FLOAT	Get_TimeSpeed() { return m_fTimeSpeed; }

private:
	vector<D3DXVECTOR3>		m_vecSavePoint;
	D3DXVECTOR3				m_vSaveDir;

	D3DXMATRIX	m_matWorld;
	D3DXMATRIX	m_matScale;
	D3DXMATRIX	m_matRot;
	D3DXMATRIX	m_matTrans;

	float		m_fTimeSpeed;
	float		m_fAngle;

};

