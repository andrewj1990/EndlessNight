#pragma once

#include "renderable.h"

class Label : public Renderable
{
public:
	Label(std::string text, float x, float y, glm::vec4 colour);

	void submit(BatchRenderer& renderer) const override;

public:
	std::string text;
	glm::vec3& position;
	float x;
	float y;

};
