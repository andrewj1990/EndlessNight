#pragma once

#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <glm\glm.hpp>
#include <string.h>

class Shader
{
public:
	Shader(const char* vert_path, const char* frag_path);

	void bind() const;
	void unbind() const;

	void setUniform1f(GLuint location, float value);
	void setUniform2f(const char* name, const glm::vec2& vector);
	void setUniformMat4(const char* name, const glm::mat4& matrix);

private:
	GLuint loadShader(const char* vertex_file, const char* frag_file);


private:
	GLuint m_ProgramID;
};

