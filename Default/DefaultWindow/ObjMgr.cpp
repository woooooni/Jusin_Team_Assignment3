
#include "stdafx.h"
#include "ObjMgr.h"


CObjMgr* CObjMgr::inst = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	for (auto& iter : m_ObjList)
	{
		for (auto& iterB : iter)
		{
			Safe_Delete(iterB);
		}

		iter.clear();
	}
}

void CObjMgr::Add_Obj(OBJ_TYPE p_Type, CObj * p_Obj)
{
	if (p_Obj == nullptr || p_Type >= OBJ_END)
		return;

	m_ObjList[p_Type].push_back(p_Obj);
}




