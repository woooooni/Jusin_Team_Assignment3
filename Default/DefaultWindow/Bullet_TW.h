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
};

