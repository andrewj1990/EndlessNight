#include "particle.h"

Particle::Particle(int x, int y, Layer& layer)
	: m_NumParticles(10), m_Life(0), m_Destroy(false), m_Layer(layer)
{
	m_TotalLife = 50 + (rand() % 50);
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	//dx /= 100.0f;
	//dy /= 100.0f;
	float colour = rand() % 1000 / 1000.0f;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(2.0f,2.0f), glm::vec4(colour, colour, 0, colour));
	m_Layer.add(m_Sprite);
}

Particle::Particle(int x, int y, Layer& layer, glm::vec4 colour)
	: m_NumParticles(10), m_Life(0), m_Destroy(false), m_Layer(layer)
{
	m_TotalLife = 50 + (rand() % 50);
	dx = 0.5f - (rand() % 1000 / 1000.0f);
	dy = 0.5f - (rand() % 1000 / 1000.0f);
	//dx /= 100.0f;
	//dy /= 100.0f;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(2.0f, 2.0f), colour);
	m_Layer.add(m_Sprite);
}

Particle::~Particle()
{
	delete m_Sprite;
}

void Particle::update()
{
	m_Sprite->fade();

	float alpha = m_Sprite->getColour().w;

	// set to destroy particle if life runs out
//	m_Life++;
	//if (++m_Life > m_TotalLife)
	if (alpha <= 0.1f)
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