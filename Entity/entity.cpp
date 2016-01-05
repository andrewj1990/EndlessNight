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

bool Entity::collision(std::vector<Entity*> objects)
{
	for (Entity* object : objects)
	{
		const int& px = object->getX();
		const int& py = object->getY();
		const int& w = object->getWidth();
		const int& h = object->getHeight();

		if (m_X < px + w && m_X > px && m_Y > py && m_Y < py + h)
		{
			//// if player is on a platform and moving
			//// get the platforms colour and spawn particles the same colour as the platfroms
			//if (spawn_particles && (dx != 0 || dy != 0))
			//{
			//	glm::vec4 colour = platform->getSprite()->getColour();
			//	m_Level.addParticle(new Particle(getCenterX(), m_Y, m_Level, colour));
			//}
			return true;
		}
	}
	return false;
}

void Entity::addToLevel(Renderable* renderable)
{
	m_Level.getLayer().add(renderable);
}