#include "enemy.h"

Enemy::Enemy(const int& x, const int& y, const int& size, Level& level)
	: Entity(x, y, level), m_Size(size), m_Health(100)
{
	m_Sprite = new Sprite(glm::vec3(x, y, 1), glm::vec2(m_Size, m_Size), glm::vec4(0.4f, 0.2f, 0, 1));

	m_Level.getLayer().add(m_Sprite);

	float speed = 50.0f / size;

	m_Dx = (0.5f - (std::rand() % 1000 / 1000.0f)) * speed;
	m_Dy = (0.5f - (std::rand() % 1000 / 1000.0f)) * speed;
}

void Enemy::update()
{
	m_Sprite->addDirection(m_Dx, m_Dy);
	m_X += m_Dx;
	m_Y += m_Dy;

	if (m_X < 0 || m_X > m_Level.getWindowClass().getWidth())
	{
		m_Dx *= -1;
	}
	
	if (m_Y < 0 || m_Y > m_Level.getWindowClass().getHeight())
	{
		m_Dy *= -1;
	}

}

void Enemy::render()
{

}

void Enemy::damage(float amount)
{
	m_Health -= amount;
	m_Destroy = m_Health <= 0;
}

void Enemy::move(const double& dx, const double& dy)
{
}

bool Enemy::collision(int x, int y)
{
	return false;
}
