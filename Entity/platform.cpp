#include "platform.h"

Platform::Platform(Level& level)
	: Entity(0, 0, level)
{
	m_X = rand() % 1280;
	m_Y = rand() % 720;
	m_Width = 100 + (rand() % 100);
	m_Height = 100 + (rand() % 100);

	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(m_Width, m_Height), glm::vec4(rand() % 1000 / 1000.0f, 0, 0, 5));
	addToLevel(m_Sprite);
}

Platform::Platform(int x, int y, int width, int height, Level& level)
	: Entity(x, y, level)
{
	m_Width = width;
	m_Height = height;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 0, 1));
	addToLevel(m_Sprite);
}

void Platform::update()
{

}

void Platform::render()
{

}