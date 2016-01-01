#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "buffers/indexbuffer.h"
#include "renderable.h"

struct VertexData
{
	glm::vec3 vertex;
	unsigned int colour;
};

const int RENDERER_MAX_SPRITES = 100000;
const int RENDERER_VERTEX_SIZE = sizeof(VertexData);
const int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
const int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
const int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;

constexpr int SHADER_VERTEX_INDEX = 0;
constexpr int SHADER_COLOUR_INDEX = 1;


class BatchRenderer
{
private:
	GLuint m_VAO;
	GLuint m_BO;
	VertexData* m_Buffer;
	IndexBuffer* m_IBO;
	GLsizei m_IndexCount;	

public:
	BatchRenderer();
	~BatchRenderer();
	void begin();
	void submit(const Renderable& renderable);
	void end();
	void flush();

private:
	void init();

};