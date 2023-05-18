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
	virtual void	Initialize(void)		PURE;
	virtual int		Update(void)			PURE;
	virtual void	Late_Update(void)		PURE;
	virtual void	Render(HDC hDC)			PURE;
	virtual void	Release(void)			PURE;

public:
	OBJ_TYPE			GetObjType()	{ return m_eObjType; };
	const D3DXVECTOR3&	GetPos()		{ return m_vPos; }

private:
	OBJ_TYPE		m_eObjType;
	D3DXVECTOR3		m_vPos;
	
};

