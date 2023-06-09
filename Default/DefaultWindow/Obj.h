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
	virtual void	Collide(OBJ_TYPE p_Type, CObj* p_Targ)	PURE;

	
	bool			Get_Dead() { return m_bDead; }
	void			Set_Dead() { m_bDead = true; }
	OBJ_TYPE		Get_Type() { return m_eObjType; }
	REND_TYPE		Get_Rend() { return m_eRendType; }


	const INFO&	Get_Info() const { return m_tInfo; }

	void			Set_Pos(VECTOR p_V)
	{
		m_tInfo.vPos = p_V;
	}

	void			Set_Name(const wstring& p_Str)
	{
		m_strName = p_Str;
	}

	void			Set_Dir(const VECTOR& p_V)
	{
		m_tInfo.vDir = p_V;
		if (D3DXVec3Length(&m_tInfo.vDir) != 0.f)
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	}


	vector<D3DXVECTOR3>&	Get_vecPoint() { return m_vecPoint; }
	FLOAT			Get_Speed() { return m_fSpeed; }


	void			Set_Speed(float& p_f) { m_fSpeed = p_f; }

protected:

protected:
	vector<D3DXVECTOR3>		m_vecPoint;

	INFO		m_tInfo;

	OBJ_TYPE	m_eObjType;
	REND_TYPE	m_eRendType;

	float		m_fSpeed;

	wstring		m_strName;

	bool		m_bDead;
};

