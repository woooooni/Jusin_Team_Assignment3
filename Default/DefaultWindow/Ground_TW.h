#pragma once
#include "Obj_TW.h"
class CGround_TW :
	public CObj_TW
{
public:
	explicit CGround_TW();
	virtual ~CGround_TW();

public:
	// CObj_TW을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

protected:
	virtual void				Update_Idle()			override;
	virtual void				Update_Move()			override;
	virtual void				Update_Jump()			override;
	virtual void				Update_Hang()			override;
	virtual void				Update_Die()			override;
	virtual void				Update_TimeRewind()		override;


public:
	virtual void OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther) override;
};

