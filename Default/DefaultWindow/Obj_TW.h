#pragma once
#include "Obj.h"
class CObj_TW :
	public CObj
{
public:
	explicit		CObj_TW(OBJ_TYPE _eType);
	virtual			~CObj_TW();

public:
	// CObj을(를) 통해 상속됨
	virtual void	Initialize(void)				PURE;
	virtual int		Update(void)					PURE;
	virtual void	Late_Update(void)				PURE;
	virtual void	Render(HDC hDC)					PURE;
	virtual void	Release(void)					PURE;


	virtual void	OnCollision(COLLISION_DIR _eDir, CObj_TW* _pOther)		PURE;
	virtual void	Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

public:
	OBJ_TYPE				GetObjType()	{ return m_eObjType; }
	const D3DXVECTOR3&		GetPos()		{ return m_vPos; }
	const D3DXVECTOR3&		GetScale()		{ return m_vScale; }

	vector<D3DXVECTOR3>		GetVertices() { return m_vecVertices; }
	vector<D3DXVECTOR3>		GetOriginVertices() { return m_vecOriginVertices; }

	void					Set_PosX(float fX) { m_vPos.x += fX; }
	void					Set_PosY(float fY) { m_vPos.y += fY; }

	void					SetPos(const D3DXVECTOR3& _vPos)		{ m_vPos = _vPos; }
	void					SetScale(const D3DXVECTOR3& _vScale)	{ m_vScale = _vScale; }
	void					SetAngle(float _fAngle)				{ m_fAngle = _fAngle; }

	void					SetGround(bool _b)	{ m_bGround = _b; }
	bool					IsGround()			{ return m_bGround; }

protected:
	void	ResetVertices();
protected:
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vScale;
	D3DXMATRIX				m_matWorld;
	float					m_fAngle;

	vector<D3DXVECTOR3>		m_vecVertices;
	vector<D3DXVECTOR3>		m_vecOriginVertices;

private:
	OBJ_TYPE				m_eObjType;
	bool					m_bGround;
	
};

