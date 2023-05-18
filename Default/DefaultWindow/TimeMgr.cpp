#include "stdafx.h"
#include "TimeMgr.h"
#include "MainGame.h"

CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_Acc(0)
	, m_iFPS(0)
	, m_fTimeScale(1.f)
{

}

CTimeMgr::~CTimeMgr()
{

}



void CTimeMgr::Initialize()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	m_dDT = (double)((m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart) * m_fTimeScale;
	m_llPrevCount = m_llCurCount;
	

	//#ifdef _DEBUG
	//	if (m_dDT > (1. / 60.))
	//		m_dDT = (1. / 60.);
	//#endif
}

void CTimeMgr::Render()
{
	++m_iCallCount;
	m_Acc += m_dDT;

	if (m_Acc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_Acc = 0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);

		SetWindowText(g_hWnd, szBuffer);
	}
}