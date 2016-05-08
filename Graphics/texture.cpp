#include "texture.h"

Texture::Texture(const std::string& filename)
	: m_FileName(filename), m_xIndex(0), m_yIndex(0)
{
	m_TID = load();
	setDefaultUV();
}

Texture::Texture(SpriteSheet& spritesheet, const std::string& filename, const int& xIndex, const int& yIndex, const int& width, const int& height)
	: m_FileName(filename), m_TID(spritesheet.getTID()), m_xIndex(xIndex), m_yIndex(yIndex)
{
	float inverseIndex = ((float)spritesheet.getHeight() / (float)height) - (float)yIndex - 1;
	setUV((float)xIndex, inverseIndex, (float)width, (float)height, (float)spritesheet.getWidth(), (float)spritesheet.getHeight());
}

void Texture::setDefaultUV()
{
	m_UV.push_back(glm::vec2(0, 0));
	m_UV.push_back(glm::vec2(0, 1));
	m_UV.push_back(glm::vec2(1, 1));
	m_UV.push_back(glm::vec2(1, 0));
}

void Texture::setUV(const float& ix, const float& iy, const float& w, const float& h, const float& sw, const float& sh)
{
	float tx = (ix * w) / sw;
	float ty = (iy * h) / sh;
	float tw = (w / sw);
	float th = (h / sh);

	m_UV.push_back(glm::vec2(tx, ty));
	m_UV.push_back(glm::vec2(tx, ty + th));
	m_UV.push_back(glm::vec2(tx + tw, ty + th));
	m_UV.push_back(glm::vec2(tx + tw, ty));
}

Texture::~Texture()
{

}

GLuint Texture::load()
{
	BYTE* pixels = loadImage(m_FileName.c_str(), m_Width, m_Height);

	GLuint result;
	glGenTextures(1, &result);
	glBindTexture(GL_TEXTURE_2D, result);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete[] pixels;
	return result;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_TID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
