#pragma once
#include "Obj.h"

class CJCollisionMgr
{
public:
	CJCollisionMgr();
	~CJCollisionMgr();

	static	void Collision_Rect(list<CObj*> Dst, list<CObj*> Src);
	static	void Collision_SphereRect(list<CObj*> Dst, vector<CObj*> Src);

	static  bool LineSphere_Collision(CObj* _pDest, CObj* _pSrc, const float& _fRad);

	static	void	Collide(CObj* _pTemp, CObj* _pSrc);

	static	void TestTile(CObj* pDst, CObj* pSrc);
};

