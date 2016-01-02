#pragma once

#include <cstdlib>
#include "../Entity/sprite.h"
#include "../Graphics/Layers/layer.h"

class Platform
{
public:
	Platform(Layer& layer);
	Platform(Layer& layer, int x, int y, int width, int height);

	void add(Layer& layer);
	void render();

	const int& getX() { return m_X; }
	const int& getY() { return m_Y; }
	const int& getWidth() { return m_Width; }
	const int& getHeight() { return m_Height; }

private:
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;

	Sprite* m_Sprite;

};