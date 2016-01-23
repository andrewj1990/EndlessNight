#pragma once

#include <cstddef>
#include <GL/glew.h>
#include "buffers/indexbuffer.h"
#include <vector>
#include <glm\glm.hpp>
#include "font.h"
#include <memory>

class Renderable;

struct VertexData
{
	glm::vec3 vertex;
	glm::vec2 uv;
	float tid;
	unsigned int colour;
};

const int RENDERER_MAX_SPRITES = 100000;
const int RENDERER_VERTEX_SIZE = sizeof(VertexData);
const int RENDERER_SPRITE_SIZE = RENDERER_VERTEX_SIZE * 4;
const int RENDERER_BUFFER_SIZE = RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES;
const int RENDERER_INDICES_SIZE = RENDERER_MAX_SPRITES * 6;
constexpr int RENDERER_MAX_TEXTURES = 32;

constexpr int SHADER_VERTEX_INDEX = 0;
constexpr int SHADER_UV_INDEX = 1;
constexpr int SHADER_TID_INDEX = 2;
constexpr int SHADER_COLOUR_INDEX = 3;


class BatchRenderer
{
private:
	GLuint m_VAO;
	GLuint m_BO;
	VertexData* m_Buffer;
	std::unique_ptr<IndexBuffer> m_IBO;
	GLsizei m_IndexCount;	

	std::vector<GLuint> m_TextureSlots;

public:
	BatchRenderer();
	~BatchRenderer();
	void begin();
	void submit(const Renderable& renderable);
	void drawString(const Font& font, const std::string& text, const glm::vec3& position, const glm::vec4& colour);
	void end();
	void flush();

private:
	void init();

};

#include "renderable.h"