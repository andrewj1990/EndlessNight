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
#include "block.h"

class Player : public Entity
{
public:
	Player(const int& x, const int& y, Level& level);

	void update() override;
	void render() override;

private:
	void move(const double& dx, const double& dy);
	void fall(const double& dy);
	bool collision(int x, int y, bool spawn_particle = false, int dx = 0, int dy = 0);
	void increaseDamage(float multiplier);

private:
	double m_PlayerSpeed;
	int m_PlayerDamage;

	int m_Anim;
	int m_ProjectileDelay;

	std::vector<Sprite*> m_PlayerBody;
	//std::unique_ptr<SpriteSheet> m_PlayerSpriteSheet;
	SpriteSheet m_PlayerSpriteSheet;
	bool first;
};