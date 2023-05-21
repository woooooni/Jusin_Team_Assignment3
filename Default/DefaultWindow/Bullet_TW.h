#pragma once
#include "Obj_TW.h"
class CBullet_TW :
	public CObj_TW
{
public:
	explicit CBullet_TW();
	virtual ~CBullet_TW();

public:
	virtual void	Initialize(void) override;
	virtual int		Update(void) override;
	virtual void	Late_Update(void) override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release(void) override;
	virtual void	OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther) override;

protected:
	virtual void				Update_Idle()			override;
	virtual void				Update_Move()			override;
	virtual void				Update_Jump()			override;
	virtual void				Update_Hang()			override;
	virtual void				Update_Die()			override;
	virtual void				Update_TimeRewind()		override;

public:
	void Parrying();

public:
	void SetDir(D3DXVECTOR3 _vDir) { m_vDir = _vDir; }

private:
	D3DXVECTOR3 m_vDir;
	float		m_fBulletSpeed;

	float		m_fDeletionTime;
	float		m_fAccDeletion;


};

