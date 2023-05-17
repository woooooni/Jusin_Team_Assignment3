#pragma once
#include	"Define.h"
class CScene
{
public:
	CScene();
	virtual ~CScene();


	virtual	void	Initialize()	PURE;
	virtual	void	Update()		PURE;
	virtual	void	Late_Update()	PURE;
	virtual	void	Render(HDC  hDC)	PURE;
	virtual	void	Release()		PURE;

	SCENE_TYPE		Get_SType() { return m_eSceneNum; }

protected:
	SCENE_TYPE	m_eSceneNum;
};
