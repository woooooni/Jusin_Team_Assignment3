#pragma once
#include "Obj.h"

class CJTile :	
	public CObj
{
public:
	CJTile();
	virtual ~CJTile();

public:
	void		Set_Tile(int _iDrawID, int _iOption)
	{
		m_iDrawID = _iDrawID;
		m_iOption = _iOption;
	}

	int			Get_DrawID() { return m_iDrawID;  }
	int			Get_Option() { return m_iOption; }

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	virtual void Collide(OBJ_TYPE p_Type, CObj * p_Targ) override;

public:
	


private:
	bool		m_bStart;

	int			m_iDrawID;
	int			m_iOption;
};

