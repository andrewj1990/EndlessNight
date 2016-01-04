#include "projectile.h"

Projectile::Projectile(int x, int y, Level& level)
	: Entity(x, y, level), m_ProjectileSpeed(5.0f)
{
	calcProjectileDir();
	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(5, 5), glm::vec4(0, 1, 0, 1));
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
	length = m_ProjectileSpeed / std::sqrtf(m_Dx*m_Dx + m_Dy*m_Dy);

	// normalize
	m_Dx *= length;
	m_Dy *= length;
}

void Projectile::update()
{
	m_Sprite->addDirection(m_Dx, m_Dy);
}

void Projectile::render()
{

}