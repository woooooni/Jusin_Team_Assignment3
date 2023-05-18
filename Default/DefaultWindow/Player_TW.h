#pragma once
#include "Obj_TW.h"

class CScene_Taewon;
class CPlayer_TW :
	public CObj_TW
{
public:
	explicit	CPlayer_TW();
	virtual		~CPlayer_TW();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;

public:
	virtual void OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther) override;

public:
	void SetScene(CScene_Taewon* _pScene) { m_pScene = _pScene; }

public:
	void ChangeState(STATE _eState);

private:
	void Input();
	void Jump();
	void Jump_Hang();
	void Shoot_Hang();
	void Shoot();
	void AddForceY(float _f) { m_fForceY += _f; }

private:
	void Update_Idle();
	void Update_Move();
	void Update_Jump();
	void Update_Hang();
	void Update_Die();
	void Update_TimeRewind();

private:
	float				m_fForceY;
	CScene_Taewon*		m_pScene;
	STATE				m_eState;
	COLLISION_DIR		m_eGroundDir;
};

