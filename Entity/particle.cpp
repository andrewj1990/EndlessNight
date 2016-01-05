#include "particle.h"

Particle::Particle(int x, int y, Level& level)
	: Entity(x, y, level)
{
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	float colour = rand() % 1000 / 1000.0f;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(5.0f,5.0f), glm::vec4(1, colour / 3.0f, 0, colour));
	addToLevel(m_Sprite);
}

Particle::Particle(int x, int y, Level& level, glm::vec4 colour, float size)
	: Entity(x, y, level)
{
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(size, size), colour);
	addToLevel(m_Sprite);
}

void Particle::update()
{
	m_Sprite->fade();

	float alpha = m_Sprite->getColour().w;
	// set to destroy particle if life runs out
	if (alpha <= 0.05f)
	{
		m_Destroy = true;
	}

	m_Sprite->addDirection(dx, dy);
}

void Particle::render()
{

}