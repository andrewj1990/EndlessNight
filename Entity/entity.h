#pragma once

#include "../Level/level.h"
#include "../Graphics/Layers/layer.h"
#include "../Graphics/window.h"
#include "sprite.h"

class Entity
{
public:
	Entity(int x, int y, Level& level, Layer& layer, Window& window);

	void update();
	void render();

	int getX() const { return m_X; }
	int getY() const { return m_Y; }

protected:
	int m_X;
	int m_Y;

	Layer& m_Layer;
	Level& m_Level;
	Window& m_Window;

	Sprite* m_Sprite;

private:

};