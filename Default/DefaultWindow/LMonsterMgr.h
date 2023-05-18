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


private:

	float		m_fLastCreateTime;

	float		m_fCreateCoolTime;
};

