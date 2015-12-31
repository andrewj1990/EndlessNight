#include "shader.h"

Shader::Shader(const char* vert_path, const char* frag_path)
{
	m_ProgramID = loadShader(vert_path, frag_path);
}

void Shader::bind() const
{
	glUseProgram(m_ProgramID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform1f(GLuint location, float value)
{
	glUniform1f(location, value);
}

void Shader::setUniform2f(const char* name, const glm::vec2& vector)
{
	bind();
	glUniform2fv(glGetUniformLocation(m_ProgramID, name), 1, &vector[0]);
	unbind();
}

void Shader::setUniformMat4(const char* name, const glm::mat4& matrix)
{
	bind();
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name), 1, GL_FALSE, &matrix[0][0]);
	unbind();
}

GLuint Shader::loadShader(const char* vertex_file_path, const char* fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	// Compile Vertex Shader
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Compile Fragment Shader
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);


	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);


	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}