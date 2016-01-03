#pragma once

#include <vector>
#include "../Entity/platform.h"
#include "../Graphics/window.h"
#include <cstdlib>
#include "../Graphics/Layers/layer.h"
#include "level.h"

class Level;

class Zone
{
public:
	Zone(const int& x, const int& y, const Window& window, Layer& layer, Level& level);

	void init();

private:
	std::vector<Entity*> m_Platforms;
	const Window& m_Window;
	Layer& m_Layer;
	Level& m_Level;

	int m_X;
	int m_Y;

};