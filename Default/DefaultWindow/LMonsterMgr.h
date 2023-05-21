#pragma once
class CLMonsterMgr
{

#pragma region Instance
private:
	CLMonsterMgr();
	~CLMonsterMgr();

	static	CLMonsterMgr*		inst;

public:

	static	CLMonsterMgr*		Get_Inst()
	{
		if (!inst)
			inst = new CLMonsterMgr;

		return inst;
	}

	static	void	Destroy_Inst()
	{
		if (inst)
		{
			delete inst;
			inst = nullptr;
		}
	}

#pragma endregion


public:
	void		Create_Monster();

	void		Reset()
	{
		m_fCreateCoolTime = 2.f;
		m_fLastCreateTime = 0.f;
		m_fLevel = 1.f;
	}

private:

	float		m_fLastCreateTime;

	float		m_fCreateCoolTime;

	float		m_fLevel;
};

