#pragma once

#include "../entity.h"
#include "../../Utils/astar.h"
#include <unordered_map>

class Projectile : public Entity
{
public:
	Projectile(int x, int y, Level& level);

	void update() override;
	void render() override;
	bool collision() override;

private:
	void calcProjectileDir();

private:
	float m_Dx;
	float m_Dy;

	float m_ProjectileSpeed;

	int m_Life;

	std::vector<Node> path;

};