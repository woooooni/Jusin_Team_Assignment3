#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render();
	void		Release(void);

private:
	HDC			m_hDC;
	HDC			m_memDC;
	HBITMAP		m_hBit;

	CObj*		m_pPlayer;

public:
	CMainGame();
	~CMainGame();
};

