#pragma once

#include "JTile.h"

class CJTileMgr
{
private:
	CJTileMgr();
	~CJTileMgr();

public:
	void Initialize(void);
	void Update(void);
	void Late_Update(void);
	void Render(HDC hDC);
	void Release(void);

public:
	void	Picking_Tile(POINT _pt, int _iDrawID, int _iOption);
	void	Save_Tile(void);
	void	Load_Tile(void);

	CObj*	Get_Tile(CObj * pObj);

	vector<CObj*>&	Get_vecTile() { return m_vecTile; }

public:
	static CJTileMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CJTileMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}

	}
private:
	static CJTileMgr*		m_pInstance;
	vector<CObj*>			m_vecTile;

};

