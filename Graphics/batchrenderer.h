#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "buffers/indexbuffer.h"
#include "renderable.h"

#define RENDERER_MAX_SPRITES	100000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX	0
#define SHADER_COLOUR_INDEX 1

struct VertexData
{
	glm::vec3 vertex;
	unsigned int colour;
};

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