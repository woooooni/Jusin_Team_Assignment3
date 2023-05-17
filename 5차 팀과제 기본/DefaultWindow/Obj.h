#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)	PURE;
	virtual void	Late_Update(void)	PURE;
	virtual void	Render(HDC hDC)	PURE;
	virtual void	Release(void)	PURE;

	
	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true; }
	OBJ_TYPE	Get_Type() { return m_eObjType; }
	REND_TYPE	Get_Rend() { return m_eRendType; }

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	OBJ_TYPE	m_eObjType;
	REND_TYPE	m_eRendType;

	float		m_fSpeed;


	bool		m_bDead;
};

