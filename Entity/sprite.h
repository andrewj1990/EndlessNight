#pragma once

#include "../Graphics/renderable.h"
#include <iostream>

class Sprite : public Renderable
{
public:
	Sprite(const glm::vec3& position, const glm::vec2 size, const glm::vec4& colour);
	~Sprite();

	void setPosition(double x, double y);
	void addDirection(double dx, double dy);

	void fade();

private:

};