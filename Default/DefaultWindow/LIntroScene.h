#pragma once
#include "Scene.h"
class CLIntroScene : public CScene
{
public:
	CLIntroScene();
	~CLIntroScene();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

