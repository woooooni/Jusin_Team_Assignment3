#pragma once

class CMyBMP
{
public:
	CMyBMP();
	~CMyBMP();


	void	Release();
	HDC		Get_DC() { return m_DC; }

	void	Load_MyImage(const TCHAR* m_str);

private:
	HDC m_DC;
	HBITMAP m_bitNowMap;
	HBITMAP m_bitOldMap;

};
