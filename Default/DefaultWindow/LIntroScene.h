#pragma once
#include "Scene.h"
class CLIntroScene : public CScene
{
public:
	CLIntroScene();
	~CLIntroScene();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

