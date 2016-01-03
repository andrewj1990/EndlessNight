#include "entity.h"

Entity::Entity(int x, int y, Level& level)
	: m_X(x), m_Y(y), m_Destroy(false), m_Level(level)
{
}

void Entity::update()
{

}

void Entity::render()
{

}

void Entity::addToLevel(Renderable* renderable)
{
	m_Level.getLayer().add(renderable);
}