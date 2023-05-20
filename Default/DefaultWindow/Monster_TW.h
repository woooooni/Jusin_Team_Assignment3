#pragma once
#include "Obj_TW.h"
class CScene_Taewon;
class CMonster_TW :
	public CObj_TW
{
public:
	explicit CMonster_TW();
	virtual ~CMonster_TW();

public:
	// CObj_TW을(를) 통해 상속됨
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	virtual void	OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther) override;

public:
	void				SetScene(CScene_Taewon* _pScene) { m_pScene = _pScene; }
	void				SetTarget(CObj_TW* _pTarget) { m_pTarget = _pTarget; }

protected:
	virtual void				Update_Idle()			override;
	virtual void				Update_Move()			override;
	virtual void				Update_Jump()			override;
	virtual void				Update_Hang()			override;
	virtual void				Update_Die()			override;
	virtual void				Update_TimeRewind()		override;

public:
	void OnDamaged(COLLISION_DIR _eDir, CObj_TW * _pOther);

private:
	float				m_fForceY;
	
	float				m_fDeletionTime;
	float				m_fAccDeletion;
	
	float				m_fFireDelayTime;
	float				m_fAccFire;

	CScene_Taewon*		m_pScene;
	D3DXVECTOR3			m_vDeadDir;

	CObj_TW*			m_pTarget;
	
};

