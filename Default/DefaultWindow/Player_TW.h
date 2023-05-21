#pragma once
#include "Obj_TW.h"

class CScene_Taewon;
class CGround_TW;
class CGhost_TW;
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

protected:
	virtual void				Update_Idle()			override;
	virtual void				Update_Move()			override;
	virtual void				Update_Jump()			override;
	virtual void				Update_Hang()			override;
	virtual void				Update_Die()			override;
	virtual void				Update_TimeRewind()		override;


private:
	void Input();
	void Jump();
	void Jump_Hang();
	void Shoot_Hang();
	void Shoot();
	void AddForceY(float _f) { m_fForceY += _f; }

	void Update_Gravity();


private:
	float				m_fForceY;
	CScene_Taewon*		m_pScene;
	COLLISION_DIR		m_eGroundDir;
	CGround_TW*			m_pGround;
	CGhost_TW*			m_pGhost;
};

