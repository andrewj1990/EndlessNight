#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "texture.h"
#include "batchrenderer.h"
	
class Renderable
{
protected:
	std::vector<glm::vec3> m_Positions;
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
	Renderable(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1,1,1,1))
		: m_Position(position), m_Size(size), m_Colour(color)
	{	
		//m_Positions.push_back(glm::vec3(position.x, position.y, position.z));
		//m_Positions.push_back(glm::vec3(position.x, position.y + size.y, position.z));
		//m_Positions.push_back(glm::vec3(position.x + size.x, position.y + size.y, position.z));
		//m_Positions.push_back(glm::vec3(position.x + size.x, position.y, position.z));

		setUV();
	}

	Renderable(const int& x0, const int& y0, const int& x1, const int& y1, const int& x2, const int& y2, const int& x3, const int& y3, const glm::vec4& color = glm::vec4(1, 1, 1, 1))
		: m_Colour(color)
	{
		m_Positions.push_back(glm::vec3(x0, y0, 0));
		m_Positions.push_back(glm::vec3(x1,	y1, 0));
		m_Positions.push_back(glm::vec3(x2,	y2, 0));
		m_Positions.push_back(glm::vec3(x3,	y3, 0));

		setUV();
	}

	virtual void submit(BatchRenderer& renderer) const
	{
		renderer.submit(*this);
	}

	void setColor(float r, float g, float b)
	{
		m_Colour.r = r;
		m_Colour.g = g;
		m_Colour.b = b;
	}

	void setTexture(Texture* texture) { m_Texture = texture; m_UV = m_Texture->getUVs(); }

	inline const std::vector<glm::vec3>& getPositions() const { return m_Positions; }
	inline const glm::vec3& getPosition() const { return m_Position; }
	inline const glm::vec2& getSize() const { return m_Size; }
	inline const glm::vec4& getColour() const { return m_Colour; }
	inline const std::vector<glm::vec2>& getUV() const { return m_UV; }
	inline const unsigned int getTID() const { return m_Texture == nullptr ? 0 : m_Texture->getTID(); }

private:
	void setUVDefaults()
	{
		//float r = rand() % 10;
		//if (r == 0) r = 1;
		//else r = 1 / r;
		float s = 0.0f;
		float r = 1.0f;
		m_UV.push_back(glm::vec2(s, s));
		m_UV.push_back(glm::vec2(s, r));
		m_UV.push_back(glm::vec2(r, r));
		m_UV.push_back(glm::vec2(r, s));
	}

	void setUV()
	{
		float totalSize = 64;
		float size = 22;

		float ix = 1;
		float iy = 1;

		float tx = (ix * size) / totalSize;
		float ty = (iy * size) / totalSize;
		float tw = (size / totalSize);
		float th = (size / totalSize);

		m_UV.push_back(glm::vec2(tx, ty));
		m_UV.push_back(glm::vec2(tx, ty + th));
		m_UV.push_back(glm::vec2(tx + tw, ty + th));
		m_UV.push_back(glm::vec2(tx + tw, ty));
	}
};