#include "perlinNoise.h"

PerlinNoise::PerlinNoise()
	: m_Frequency(2), m_Persistence(0.25), m_NumOctaves(6)
{
}

double PerlinNoise::calcPerlinNoise(float x, float y)
{
	double total = 0;

	double freq = 2;
	double amplitude = 1;

	for (int i = 0; i < m_NumOctaves; ++i)
	{
		freq = std::pow(2, i);
		total += interpolateNoise(x * freq, y * freq) * amplitude;

		amplitude = std::pow(m_Persistence, i);

	}

	return total;
}

double PerlinNoise::noise(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double PerlinNoise::interpolate(float a, float b, float x)
{
	double ft = x * 3.1415927;
	double f = (1 - std::cos(ft)) * 0.5;

	return a * (1 - f) + b * f;
}

double PerlinNoise::smoothNoise(int x, int y)
{
	double corners = noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y + 1) / 16.0;
	double sides = noise(x - 1, y) + noise(x + 1, y) + noise(x, y - 1) + noise(x, y + 1) / 8.0;
	double center = noise(x, y) / 4.0;
	return corners + sides + center;
}

double PerlinNoise::interpolateNoise(float x, float y)
{
	int ix = (int)x;
	int iy = (int)y;
	float fx = x - ix;
	float fy = y - iy;

	double v1 = smoothNoise(ix	 ,  iy	);
	double v2 = smoothNoise(ix + 1, iy	);
	double v3 = smoothNoise(ix	 ,  iy + 1);
	double v4 = smoothNoise(ix + 1, iy + 1);

	double i1 = interpolate(v1, v2, ix);
	double i2 = interpolate(v3, v4, ix);

	return interpolate(i1, i2, iy);
}
