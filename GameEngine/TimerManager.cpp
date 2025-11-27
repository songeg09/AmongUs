#include "pch.h"
#include "TimerManager.h"
#include "Core.h"

TimerManager::TimerManager()
{
	m_dAccTime = 0.0;
	m_dDeltaTime = 0.0;
	m_iCallCount = 0;
	m_iFPS = 0;
	m_llFrequency = {};
	m_llPrevCount = {};
	m_bPause = false;
}

TimerManager::~TimerManager()
{

}

void TimerManager::Init()
{
	m_iCallCount = 0;
	m_dAccTime = 0.0;

	QueryPerformanceCounter(&m_llPrevCount);

	QueryPerformanceFrequency(&m_llFrequency);
	m_bPause = false;
}

void TimerManager::Update()
{
	LARGE_INTEGER llCurCount;
	QueryPerformanceCounter(&llCurCount);

	if (m_bPause == false)
		m_dDeltaTime = (double)(llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	else
		m_dDeltaTime = 0;

	m_llPrevCount = llCurCount;

	++m_iCallCount;
	m_dAccTime += m_dDeltaTime;
	if (m_dAccTime >= 1)
	{
		m_iFPS = m_iCallCount;
		m_dAccTime = 0.0;
		m_iCallCount = 0;
	}
}