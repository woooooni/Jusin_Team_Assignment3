#pragma once
#include "Scene.h"
class CJScene :
	public CScene
{
public:
	CJScene();
	virtual ~CJScene();

	// Inherited via CScene
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void GameOver();
	void GameClear();

private:
	int		m_iDrawTile;

	bool	m_bGameStart;
	bool	m_bGameOver;
	int		m_iCount;

	HFONT		hTitleFont;
	HFONT		hOldFont;

	TCHAR		m_szCount[32];
	DWORD		m_dwTime;
};

