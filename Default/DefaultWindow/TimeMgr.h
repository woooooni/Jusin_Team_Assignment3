#pragma once

class CTimeMgr
{
	SINGLETON(CTimeMgr);

private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	LARGE_INTEGER	m_llPrevCount;

	double			m_dDT;			// 프레임 간의 시간값.
	double			m_Acc;			// 1초 체크를 위한 누적 시간
	UINT			m_iCallCount;	// 함수 호출 횟수 체크
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
