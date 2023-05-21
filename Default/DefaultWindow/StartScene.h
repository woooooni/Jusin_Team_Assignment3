#pragma once
#include "Scene.h"
class CStartScene :
	public CScene
{
public:
	CStartScene();
	virtual ~CStartScene();

public:
	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	float m_fGameTime;
};

