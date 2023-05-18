#pragma once

#include "Obj_TW.h"

class CCollisionMgr_TW
{
	SINGLETON(CCollisionMgr_TW);

public:
	static void	Collision_RectEx(vector<CObj_TW*> _Dest, vector<CObj_TW*> _Sour, bool _bIsPush);
	static bool Check_Rect(CObj_TW * pDest, CObj_TW * pSour, float * pX, float * pY);

};

