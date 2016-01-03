#pragma once

#include <vector>
#include <ctime>
#include "entity.h"

class Particle : public Entity
{
public:
	Particle(int x, int y, Level& level);
	Particle(int x, int y, Level& level, glm::vec4 colour);
	~Particle() override;

	void update() override;
	void render() override;

private:
	int m_NumParticles;
	int m_TotalLife;
	float dx;
	float dy;
};