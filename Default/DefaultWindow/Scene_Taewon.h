#pragma once
#include "Scene.h"
class CScene_Taewon :
	public CScene
{
public:
	CScene_Taewon();
	virtual ~CScene_Taewon();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

