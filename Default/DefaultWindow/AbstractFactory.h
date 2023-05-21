#pragma once
#include	"Obj.h"
#include	"Define.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}

	static	CObj*	Create()
	{
		CObj*		rObj = new T();
		rObj->Initialize();

		return rObj;

	}

	static	CObj*	Create(VECTOR p_V)
	{
		CObj*		rObj = new T();
		rObj->Initialize();
		rObj->Set_Pos(p_V);


		return rObj;

	}

	static	CObj*	Create(VECTOR p_V, VECTOR p_D)
	{
		CObj*		rObj = new T();
		rObj->Initialize();
		rObj->Set_Pos(p_V);
		rObj->Set_Dir(p_D);


		return rObj;

	}

	static	CObj*	Create(INFO p_Info)
	{
		CObj*		rObj = new T(p_Info);
		rObj->Initialize();

		return rObj;

	}


};

