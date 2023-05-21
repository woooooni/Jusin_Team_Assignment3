#pragma once
#include	"Scene.h"


class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
	static		CSceneMgr*		inst;

	CScene*			m_pCurScene;
	CScene*			m_pCurMap;
	SCENE_TYPE		m_eNextType;

public:
	static		CSceneMgr*		Get_Inst()
	{
		if (inst == nullptr)
		{
			inst = new CSceneMgr;
		}

		return inst;
	}

	void		Set_SceneChange(SCENE_TYPE p_Type) { m_eNextType = p_Type; }

	SCENE_TYPE	Get_CurScene() { return m_pCurScene->Get_SType(); }

	void	Initialize();


	void	Update()
	{
		m_pCurScene->Update();

	}
	void	Late_Update()
	{
		m_pCurScene->Late_Update();

	}
	void	Render(HDC hDC)
	{
		m_pCurScene->Render(hDC);
	}

	void	Release()
	{
		m_pCurScene->Release();
		Safe_Delete<CScene*>(m_pCurScene);

		if (nullptr != inst)
		{
			delete inst;
			inst = nullptr;
		}
		
	}

	void		Check_SceneChange()
	{
		if (m_eNextType != SCENE_END && m_eNextType != m_pCurScene->Get_SType())
		{
			Change_Scene(m_eNextType);
			m_eNextType = SCENE_END;
		}
	}

	void		Change_Scene(SCENE_TYPE p_Type);


};
