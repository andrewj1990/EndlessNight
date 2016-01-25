#pragma once

#include "../Graphics/renderable.h"
#include "../Graphics/Layers/layer.h"
#include "../Graphics/window.h"
#include "entity.h"
#include "sprite.h"
#include "../Level/level.h"
#include <vector>
#include "platform.h"
#include "Projectiles\projectile.h"

class Player : public Entity
{
public:
	Player(const int& x, const int& y, Level& level);

	void update() override;
	void render() override;

private:
	void move(const double& dx, const double& dy);
	bool collision(int x, int y, bool spawn_particle = false, int dx = 0, int dy = 0);

private:
	double m_PlayerSpeed;

	std::vector<Sprite*> m_PlayerBody;
};