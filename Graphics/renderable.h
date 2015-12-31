#pragma once

#include <glm/glm.hpp>

//struct VertexData
//{
//	glm::vec3 vertex;
//	//	vec4 colour;
//	unsigned int colour;
//};

class Renderable
{
protected:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec4 m_Colour;

public:
	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: m_Position(position), m_Size(size), m_Colour(color)
	{
	}

	inline const glm::vec3& getPosition() const { return m_Position; }
	inline const glm::vec2& getSize() const { return m_Size; }
	inline const glm::vec4& getColour() const { return m_Colour; }


};