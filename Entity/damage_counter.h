#pragma once

#include "../Graphics/label.h"

class DamageCounter
{
public:
	DamageCounter(std::string text, const float& x, const float& y);

	void update();
	bool shouldDestroy() const { return m_Destroy; };

	const std::unique_ptr<Label>& getLabel() { return m_Label; }

private:
	std::unique_ptr<Label> m_Label;
	float counter;
	float m_Dx;

	bool m_Destroy;

};