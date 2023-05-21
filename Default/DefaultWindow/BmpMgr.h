#pragma once

#include	"Define.h"
#include	<map>
#include	"MyBmp.h"
class CBmpMgr
{
	SINGLETON(CBmpMgr);


public:
	void	Release();
	void	Insert_Image(const TCHAR* p_Root, const TCHAR* p_Key);
	HDC		Get_Image(const TCHAR*	p_Key);



private:
	map<const TCHAR*, CMyBMP*> m_mImageName;


};

