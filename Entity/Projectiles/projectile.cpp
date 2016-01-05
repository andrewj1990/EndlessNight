#include "projectile.h"

Projectile::Projectile(int x, int y, Level& level)
	: Entity(x, y, level), m_ProjectileSpeed(15.0f), m_Life(10000)
{
	calcProjectileDir();
	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(2.5f, 2.5f), glm::vec4(1, 1, 0, 1));
	addToLevel(m_Sprite);
}

void Projectile::calcProjectileDir()
{
	double mouseX;
	double mouseY;
	m_Level.getWindowClass().getMousePos(mouseX, mouseY);
	mouseX += m_Level.getOffset().x;
	mouseY += m_Level.getOffset().y;

	// get projectile direction
	m_Dx = mouseX - m_X;
	m_Dy = mouseY - m_Y;

	float length;
	length = std::sqrtf(m_Dx*m_Dx + m_Dy*m_Dy);

	// normalize
	m_Dx /= length;
	m_Dy /= length;
	m_Dx *= m_ProjectileSpeed;
	m_Dy *= m_ProjectileSpeed;
}

void Projectile::update()
{
	m_X += m_Dx;
	m_Y += m_Dy;

	if (!collision(m_Level.getPlatforms()))
	{
		m_Sprite->addDirection(m_Dx, m_Dy);
	}
	else {
		m_Destroy = true;
	}

	m_Sprite->fade();

	float alpha = m_Sprite->getColour().w;
	// set to destroy particle if life runs out
	if (alpha <= 0.05f)
	{
		m_Destroy = true;
	}

	if (--m_Life < 0)
	{
		m_Destroy = true;
	}
}

bool Projectile::collision(std::vector<Entity*> objects)
{
	// look at all the platforms in the level and check for any collisions
	std::vector<Entity*>& platforms = m_Level.getPlatforms();
	for (Entity* platform : platforms)
	{
		const int& px = platform->getX();
		const int& py = platform->getY();
		const int& w = platform->getWidth();
		const int& h = platform->getHeight();

		if (m_X < px + w && m_X > px && m_Y > py && m_Y < py + h)
		{
	//		std::cout << "x : " << x << ", y : " << y << "\n";
			// if player is on a platform and moving
			// get the platforms colour and spawn particles the same colour as the platfroms
			glm::vec4 platformColour = platform->getSprite()->getColour();
			for (int i = 0; i < 20; ++i)
				m_Level.addParticle(new Particle(m_X, m_Y, m_Level, platformColour, 3.0f));
			return true;
		}
	}

	return false;
}

void Projectile::render()
{

}