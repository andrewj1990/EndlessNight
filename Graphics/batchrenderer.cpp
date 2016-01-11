#include "batchrenderer.h"

BatchRenderer::BatchRenderer()
	: m_IndexCount(0)
{
	init();
}

BatchRenderer::~BatchRenderer()
{
	delete m_IBO;
}

void BatchRenderer::init()
{
	// initialize vertex array object and bind
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// initialize and bind buffer object
	glGenBuffers(1, &m_BO);
	glBindBuffer(GL_ARRAY_BUFFER, m_BO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_COLOUR_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::colour)));

	// unbind buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
//	GLuint indices[RENDERER_INDICES_SIZE];

	// get the vertices for each triangle to create a square
	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	// create a index buffer object with all the indices
	m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	// unbind the vertex array object
	glBindVertexArray(0);

}

void BatchRenderer::begin()
{
	// bind the buffer object and map the buffer to be written to
	glBindBuffer(GL_ARRAY_BUFFER, m_BO);
	m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer::submit(const Renderable& renderable)
{
	const glm::vec3& position = renderable.getPosition();
	const glm::vec2& size = renderable.getSize();
	const glm::vec4& colour = renderable.getColour();
	const std::vector<glm::vec2>& uv = renderable.getUV();

	int r = colour.x * 255;
	int g = colour.y * 255;
	int b = colour.z * 255;
	int a = colour.w * 255;

	unsigned int color = a << 24 | b << 16 | g << 8 | r;

	m_Buffer->vertex = position;
	m_Buffer->uv = uv[0];
	m_Buffer->colour = color;
	++m_Buffer;

	m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
	m_Buffer->uv = uv[1];
	m_Buffer->colour = color;
	++m_Buffer;

	m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
	m_Buffer->uv = uv[2];
	m_Buffer->colour = color;
	++m_Buffer;

	m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
	m_Buffer->uv = uv[3];
	m_Buffer->colour = color;
	++m_Buffer;

	m_IndexCount += 6;
}

void BatchRenderer::end()
{
	// unmap and unbind buffer
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// draw the quads in the buffer
void BatchRenderer::flush()
{
	glBindVertexArray(m_VAO);
	m_IBO->bind();

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	m_IBO->unbind();
	glBindVertexArray(0);

	m_IndexCount = 0;
}