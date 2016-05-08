#include "damage_counter.h"

DamageCounter::DamageCounter(std::string text, const float& x, const float& y)
	: counter(0), m_Destroy(false)
{
	m_Label = std::unique_ptr<Label>(new Label(text, x, y, FontManager::get("Arial"), glm::vec4(1, 1, 1, 1)));

	m_Dx = (0.5f - (std::rand() % 1000 / 1000.0f)) * 2.0f;
}

void DamageCounter::update()
{
	if (counter > 5.4f)
	{
		m_Destroy = true;
		return;
	}
	counter += 0.2f;
	m_Label->position.y += std::sinf(counter) * 5;
	m_Label->position.x += m_Dx;

}
