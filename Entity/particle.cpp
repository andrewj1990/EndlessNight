#include "particle.h"

Particle::Particle(int x, int y, Level& level)
	: Entity(x, y, level)
{
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	float colour = rand() % 1000 / 1000.0f;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(5.0f,5.0f), glm::vec4(colour, colour, 0, colour));
	addToLevel(m_Sprite);
}

Particle::Particle(int x, int y, Level& level, glm::vec4 colour)
	: Entity(x, y, level)
{
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(2.0f, 2.0f), colour);
	addToLevel(m_Sprite);
}

Particle::~Particle()
{
	delete m_Sprite;
}

void Particle::update()
{
	m_Sprite->fade();

	float alpha = m_Sprite->getColour().w;

//	m_Life++;
	//if (++m_Life > m_TotalLife)
	// set to destroy particle if life runs out
	if (alpha <= 0.1f)
	{
		m_Destroy = true;
	}

	m_Sprite->addDirection(dx, dy);
}

void Particle::render()
{

}