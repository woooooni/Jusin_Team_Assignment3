#pragma once

class CTimeMgr
{
	SINGLETON(CTimeMgr);

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llPrevCount;

	double			m_dDT;			// ������ ���� �ð���.
	double			m_Acc;			// 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS;
	float			m_fTimeScale;

public:
	void Initialize();
	void Update();
	void Render();

public:
	float	GetTimeScale()					{ return m_fTimeScale; }
	void	SetTimeScale(float _fScale)		{ m_fTimeScale = _fScale; }
	float	GetfDT()						{ return (float)m_dDT; }
};
