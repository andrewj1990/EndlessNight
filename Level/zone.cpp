#include "zone.h"

Zone::Zone(const int& x, const int& y, const Window& window, Layer& layer, Level& level)
	: m_X(x), m_Y(y), m_Window(window), m_Layer(layer), m_Level(level)
{
	init();
}

void Zone::init()
{
	int numberPlatforms = rand() % 50;
	
	for (int i = 0; i < numberPlatforms; ++i)
	{
		int rx = m_X + (rand() % m_Window.getWidth());
		int ry = m_Y + (rand() % m_Window.getHeight());
		int rw = rand() % m_Window.getWidth() / 5;
		int rh = rand() % m_Window.getHeight() / 5;
		//m_Level.addPlatform(new Platform(rx, ry, rw, rh, m_Level));
	}
}