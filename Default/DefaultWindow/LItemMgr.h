#pragma once


class CLItemMgr
{
	SINGLETON(CLItemMgr);
	
public:

	void    Create_Item();

	void		Reset()
	{
		m_fCreateCoolTime = 0.f;
		m_fLastCreateTime = 0.f;
	}

private:


	float		m_fLastCreateTime;

	float		m_fCreateCoolTime;
};

