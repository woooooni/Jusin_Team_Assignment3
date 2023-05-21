#include "stdafx.h"
#include "BmpMgr.h"
#include "Define.h"
#include	<algorithm>

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Release()
{
	for (auto& iter : m_mImageName)
	{
		Safe_Delete(iter.second);
	}

	m_mImageName.clear();
}

void CBmpMgr::Insert_Image(const TCHAR * p_Root, const TCHAR * p_Key)
{
	auto iter = find_if(m_mImageName.begin(), m_mImageName.end(), tagFinder(p_Key));
	if (iter == m_mImageName.end())
	{
		CMyBMP* inB = new CMyBMP;
		inB->Load_MyImage(p_Root);
		m_mImageName.insert({ p_Key, inB });
	}
}

HDC CBmpMgr::Get_Image(const TCHAR * p_Key)
{
	auto iter = find_if(m_mImageName.begin(), m_mImageName.end(), tagFinder(p_Key));
	if (iter == m_mImageName.end())
		return nullptr;


	return iter->second->Get_DC();
}