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
	void ChangeState(STATE _eState);

private:
	void Update_Idle();
	void Update_Move();
	void Update_Jump();
	void Update_Hang();
	void Update_Die();
	void Update_TimeRewind();

private:
	float				m_fForceY;
	float				m_fForceX;

	CScene_Taewon*		m_pScene;
	STATE				m_eState;
	D3DXVECTOR3			m_vDeadDir;
	
};

