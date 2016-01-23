#include "sprite.h"


Sprite::Sprite(const glm::vec3& position, const glm::vec2 size, const glm::vec4& colour)
	: Renderable(position, size, colour)
{

}

Sprite::Sprite(const glm::vec3 & position, const glm::vec2 size, Texture* texture)
	: Renderable(position, size)
{
	m_Texture = texture;
}

Sprite::~Sprite()
{

}

void Sprite::setPosition(double x, double y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Sprite::addDirection(double dx, double dy)
{
	m_Position.x += dx;
	m_Position.y += dy;
}

void Sprite::fade(float fadeAmount)
{
	m_Colour.w -= fadeAmount;
}