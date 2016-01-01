#pragma once

#include "../Graphics/renderable.h"
#include "../Graphics/Layers/layer.h"
#include "sprite.h"
#include <vector>

class Player
{
public:
	Player(const int& x, const int& y, Layer& layer);

	void update(const double& dx, const double& dy);
	void render();

	int getX() const { return m_X; }
	int getY() const { return m_Y; }

private:
	int m_X;
	int m_Y;
	Renderable* m_Renderable;
	Layer& m_Layer;

	Sprite* player_body;
	std::vector<Sprite*> m_PlayerBody;
};