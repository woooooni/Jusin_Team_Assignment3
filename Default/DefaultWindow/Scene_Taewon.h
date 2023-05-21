#pragma once
#include "Scene.h"

class CObj_TW;
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

public:
	const	vector<CObj_TW*>& GetObjVec(OBJ_TYPE _eType)			{ return m_arrVecObj[(int)_eType]; }
	void	AddObj(CObj_TW* _pObj);
	void	TimeRewind();


private:
	vector<CObj_TW*> m_arrVecObj[(int)OBJ_TYPE::OBJ_END];
	bool		m_bGuide;
};

