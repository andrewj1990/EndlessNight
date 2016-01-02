#include "platform.h"

Platform::Platform(Layer& layer)
{
	m_X = rand() % 1280;
	m_Y = rand() % 720;
	m_Width = 100 + (rand() % 100);
	m_Height = 100 + (rand() % 100);

	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(m_Width, m_Height), glm::vec4(1, 1, 0, 1));
	layer.add(m_Sprite);
}

Platform::Platform(Layer& layer, int x, int y, int width, int height)
	: m_X(x), m_Y(y), m_Width(width), m_Height(height)
{
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(1, 1, 0, 1));
	layer.add(m_Sprite);
}

void Platform::add(Layer& layer)
{
	layer.add(m_Sprite);
}

void Platform::render()
{

}