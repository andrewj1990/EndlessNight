#include "block.h"

Block::Block(float x, float y)
	: Sprite(glm::vec3(x, y, 1), glm::vec2(100, 100), glm::vec4(1, 1, 1, 1)), m_X(x), m_Y(y)
{

}

