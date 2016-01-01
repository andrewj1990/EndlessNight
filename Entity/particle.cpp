#include "particle.h"

Particle::Particle(int x, int y, Layer& layer)
	: m_NumParticles(10), m_Life(0), m_Destroy(false), m_Layer(layer)
{

	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	//dx /= 100.0f;
	//dy /= 100.0f;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(5.0f,5.0f), glm::vec4(dx,dy,0,dx));
	m_Layer.add(m_Sprite);
}

void Particle::update()
{
	// set to destroy particle if life runs out
	m_Life++;
	if (++m_Life > 10000)
	{
		m_Destroy = true;
	}

	m_Sprite->addDirection(dx, dy);
}

bool Particle::shouldDestroy() const
{
	return m_Destroy;
}

void Particle::render()
{

}