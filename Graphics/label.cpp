#include "label.h"

Label::Label(std::string text, float x, float y, glm::vec4 colour)
	: Renderable(), text(text), position(m_Position)
{
	m_Position = glm::vec3(x, y, 0.0f);
	m_Colour = colour;
}

void Label::submit(BatchRenderer& renderer) const
{
	renderer.drawString(text, m_Position, m_Colour);
}