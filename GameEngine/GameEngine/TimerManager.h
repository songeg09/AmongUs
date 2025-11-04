#pragma once
class TimerManager
{
	SINGLETON(TimerManager)
private:
	LARGE_INTEGER m_llPrevCount; // 이전 연산 처리 횟수
	LARGE_INTEGER m_llFrequency; // 1초당 연산처리 횟수

	double m_dDeltaTime;
	double m_dAccTime;
	unsigned int m_iCallCount;
	unsigned int m_iFPS;
public:
	void Init();
	void Update();
	inline double GetdDeltaTime() { return m_dDeltaTime; }
	inline float GetfDeltaTime() { return (float)m_dDeltaTime; }
	inline unsigned intGetFPS() { return m_iFPS; }
};

