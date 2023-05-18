#pragma once
#include "Obj_TW.h"
class CLaser_TW :
	public CObj_TW
{
public:
	explicit	CLaser_TW();
	virtual		~CLaser_TW();

public:
	// CObj_TW을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(COLLISION_DIR _eDir, CObj_TW * _pOther) override;

public:
	void SetDir(D3DXVECTOR3 _vDir) { m_vDir = _vDir; }
	
private:
	D3DXVECTOR3		m_vDir;
	float			m_fLen;
};

