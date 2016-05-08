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

	typedef std::pair<int, Node> Element;
	std::priority_queue<Element, std::vector<Element>, std::greater<Element>> frontier;
	Node* goal;
	Node* start;

	std::unordered_map<int, Node> came_from;
	std::unordered_map<int, int> cost_so_far;

};