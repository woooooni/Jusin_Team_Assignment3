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

	static	CObj*	Create(INFO p_Info)
	{
		CObj*		rObj = new T(p_Info);
		rObj->Initialize();

		return rObj;

	}


};

