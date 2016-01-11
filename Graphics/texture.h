#pragma once

#include "../Utils/loadImage.h"
#include <GL\glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& filename);
	~Texture();

	GLuint getTID() const { return m_TID; }
	void bind() const;
	void unbind() const;

private:
	GLuint load();

private:
	std::string m_FileName;
	GLuint m_TID;
	unsigned int m_Width;
	unsigned int m_Height;

};