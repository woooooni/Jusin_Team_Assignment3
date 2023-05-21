#pragma once
#include "Obj.h"
class CJBall :
	public CObj
{
public:
	CJBall();
	virtual ~CJBall();

	// Inherited via CObj
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

public:
	FLOAT	Get_Rad() { return m_fRad; }
	void	Add_Speed(float _fSpeed) { m_fSpeed += _fSpeed; }
	void	De_Speed(float _fSpeed) { m_fSpeed -= _fSpeed; }

private:
	void	Tile_Coli();

private:
	vector<D3DXVECTOR3>		m_vecSavePoint;
	D3DXVECTOR3				m_vSaveDir;
	D3DXVECTOR3				m_vSavePos;
	

	D3DXMATRIX	m_matWorld;
	D3DXMATRIX	m_matScale;
	D3DXMATRIX	m_matRot;
	D3DXMATRIX	m_matTrans;

	float		m_fAngle;
	float		m_fRad;

	float		m_fTimeSpeed;
	int			m_iSpeedCount;

	bool		m_bDirChange;
	bool		m_bColi;
};

