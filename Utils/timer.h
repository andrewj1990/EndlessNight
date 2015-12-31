#pragma once
#include <Windows.h>
#include <iostream>
#include <ctime>

class Timer
{
public:
	Timer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_Start);
		m_start = clock();
	}

	void reset()
	{
		QueryPerformanceCounter(&m_Start);
	}

	float elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;

		return (float)(cycles * m_Frequency);
	}

	void reset2()
	{
		m_start = clock();
	}

	float elapsed2()
	{
		return (float)(clock() - m_start);
	}

private:
	LARGE_INTEGER m_Start;
	double m_Frequency;
	clock_t m_start;
};