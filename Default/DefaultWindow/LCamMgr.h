#pragma once
class CLCamMgr
{
	SINGLETON(CLCamMgr);



public:
	void		Plus_Campos(VECTOR p_V)
	{
		m_vCampos += p_V;
	}

	void		Plus_Scale(float p_F)
	{
		m_fScale += p_F;
	}

	float		Get_Scale() { return m_fScale; }

	VECTOR Get_ScreenPos(const VECTOR& p_V);

private:
	VECTOR		m_vCampos;
	float		m_fScale;
};

