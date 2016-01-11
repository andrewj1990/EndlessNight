#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "texture.h"

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
	std::vector<glm::vec2> m_UV;
	Texture* m_Texture;
	
protected:
	Renderable()
	{
		setUVDefaults();
	}

public:
	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		: m_Position(position), m_Size(size), m_Colour(color)
	{	
		setUVDefaults();
	}

	inline const glm::vec3& getPosition() const { return m_Position; }
	inline const glm::vec2& getSize() const { return m_Size; }
	inline const glm::vec4& getColour() const { return m_Colour; }
	inline const std::vector<glm::vec2>& getUV() const { return m_UV; }
	inline const unsigned int getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getTID(); }

private:
	void setUVDefaults()
	{
		m_UV.push_back(glm::vec2(0, 0));
		m_UV.push_back(glm::vec2(0, 1));
		m_UV.push_back(glm::vec2(1, 1));
		m_UV.push_back(glm::vec2(1, 0));
	}
};