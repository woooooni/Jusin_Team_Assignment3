#pragma once


class CLItemMgr
{
	SINGLETON(CLItemMgr);
	
public:

	void    Create_Item();

	float		m_fLastCreateTime;

	float		m_fCreateCoolTime;
};

