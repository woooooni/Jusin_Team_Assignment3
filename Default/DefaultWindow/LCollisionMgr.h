#pragma once
#include	"Obj.h"
class CLCollisionMgr
{
public:
	CLCollisionMgr();
	~CLCollisionMgr();


	static	void	Collide(CObj* p_First, CObj* p_Second);
};

