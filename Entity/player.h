#pragma once

#include "../Graphics/renderable.h"
#include "../Graphics/Layers/layer.h"
#include "../Graphics/window.h"
#include "sprite.h"
#include "../Level/level.h"
#include <vector>
#include "platform.h"

class Level;

class Player
{
public:
	Player(const int& x, const int& y, Layer& layer, Level& level, Window& window);

	void update();
	void render();

	int getX() const { return m_X; }
	int getY() const { return m_Y; }

private:
	void init();
	void move(const double& dx, const double& dy);
	bool collision(int x, int y);

private:
	int m_X;
	int m_Y;
	double m_PlayerSpeed;
	Layer& m_Layer;
	Level& m_Level;
	Window& m_Window;

	Sprite* player_body;
	std::vector<Sprite*> m_PlayerBody;
};