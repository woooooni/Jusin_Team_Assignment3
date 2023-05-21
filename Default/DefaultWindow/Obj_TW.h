#pragma once
#include "Obj.h"

struct TIME_STAMP
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vScale;
	float			fAngle;
	bool			bActive;
};

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
	virtual void	Late_Update(void);
	virtual void	Render(HDC hDC)					PURE;
	virtual void	Release(void)					PURE;

public:
	virtual void	OnCollision(COLLISION_DIR _eDir, CObj_TW* _pOther)		PURE;
	virtual void	Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

public:
	void					SetObjType(OBJ_TYPE _eType)		{ m_eObjType = _eType; }
	OBJ_TYPE				GetObjType()					{ return m_eObjType; }
	const D3DXVECTOR3&		GetPos()						{ return m_vPos; }
	const D3DXVECTOR3&		GetScale()						{ return m_vScale; }
	float					GetAngle()						{ return m_fAngle; }

	vector<D3DXVECTOR3>		GetVertices() { return m_vecVertices; }
	vector<D3DXVECTOR3>		GetOriginVertices() { return m_vecOriginVertices; }

	void					Set_PosX(float fX) { m_vPos.x += fX; }
	void					Set_PosY(float fY) { m_vPos.y += fY; }

	void					SetPos(const D3DXVECTOR3& _vPos)		{ m_vPos = _vPos; }
	void					SetScale(const D3DXVECTOR3& _vScale)	{ m_vScale = _vScale; }
	void					SetAngle(float _fAngle)				{ m_fAngle = _fAngle; }

	void					SetGround(bool _b)	{ m_bGround = _b; }
	bool					IsGround()			{ return m_bGround; }

	void					SetActive(bool _b)	{ m_bActive = _b; }
	bool					IsActive()			{ return m_bActive; }

	void					SetDelete(bool _b) { m_bDelete = _b; }
	bool					IsDelete()		   { return m_bDelete; }

	stack<TIME_STAMP>&		GetTimeStamp()		{ return m_stackTimeStamp; }

	const STATE&			GetState() { return m_eState; }

public:
	virtual					void	ChangeState(STATE _eState);

protected:
	virtual void				Update_Idle()				PURE;
	virtual void				Update_Move()				PURE;
	virtual void				Update_Jump()				PURE;
	virtual void				Update_Hang()				PURE;
	virtual void				Update_Die()				PURE;
	virtual void				Update_TimeRewind()			PURE;

protected:
	void					ResetVertices();
	void					Update_TimeStamp();



protected:
	D3DXVECTOR3				m_vPos;
	D3DXVECTOR3				m_vScale;
	D3DXMATRIX				m_matWorld;
	float					m_fAngle;

	vector<D3DXVECTOR3>		m_vecVertices;
	vector<D3DXVECTOR3>		m_vecOriginVertices;

	stack<TIME_STAMP>		m_stackTimeStamp;

	STATE					m_eState;

private:
	OBJ_TYPE				m_eObjType;
	bool					m_bGround;
	bool					m_bActive;
	bool					m_bDelete;

	float					m_fTimeStampDelay;
	float					m_fAccTimeStamp;
};

