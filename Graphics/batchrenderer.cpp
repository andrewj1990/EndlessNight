#include "batchrenderer.h"

BatchRenderer::BatchRenderer()
	: m_IndexCount(0)
{
	m_TransformationStack.push_back(glm::mat4(1.0));
	//m_TransformationBack = std::make_unique<glm::mat4>(&m_TransformationStack.back());
	init();
}

BatchRenderer::~BatchRenderer()
{
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
	glEnableVertexAttribArray(SHADER_TID_INDEX);
	glEnableVertexAttribArray(SHADER_COLOUR_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
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
	m_IBO = std::unique_ptr<IndexBuffer>(new IndexBuffer(indices, RENDERER_INDICES_SIZE));

	// unbind the vertex array object
	glBindVertexArray(0);

	//m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
	//m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 80, "LuckiestGuy.ttf");
	////m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 20, "Arial.ttf");

	//ftgl::texture_glyph_t *glyph = texture_font_get_glyph(m_FTFont, 'A');

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
	const std::vector<glm::vec3>& positions = renderable.getPositions();
	const glm::vec2& size = renderable.getSize();
	const glm::vec4& colour = renderable.getColour();
	const std::vector<glm::vec2>& uv = renderable.getUV();
	const unsigned int tid = renderable.getTID();

	unsigned int color = 0;

	float ts = 0.0f;
	if (tid > 0)
	{
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); ++i)
		{
			if (m_TextureSlots[i] == tid)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES)
			{
				end();
				flush();
				begin();
			}
			m_TextureSlots.push_back(tid);
			ts = (float)(m_TextureSlots.size());
		}

	}
	int r = colour.x * 255;
	int g = colour.y * 255;
	int b = colour.z * 255;
	int a = colour.w * 255;

	color = a << 24 | b << 16 | g << 8 | r;

	//m_Buffer->vertex = positions[0];
	//m_Buffer->vertex = positions.size() > 0 ? positions[0] : position;
	m_Buffer->vertex = multiply(m_TransformationStack.back(), positions.size() > 0 ? positions[0] : position);
	//m_Buffer->vertex = position;
	m_Buffer->uv = uv[0];
	m_Buffer->tid = ts;
	m_Buffer->colour = color;
	++m_Buffer;

	//m_Buffer->vertex = positions[1];
	//m_Buffer->vertex = positions.size() > 0 ? positions[1] : glm::vec3(position.x, position.y + size.y, position.z);
	m_Buffer->vertex = multiply(m_TransformationStack.back(), positions.size() > 0 ? positions[1] : glm::vec3(position.x, position.y + size.y, position.z));
	//m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
	m_Buffer->uv = uv[1];
	m_Buffer->tid = ts;
	m_Buffer->colour = color;
	++m_Buffer;

	//m_Buffer->vertex = positions[2];
	//m_Buffer->vertex = positions.size() > 0 ? positions[2] : glm::vec3(position.x + size.x, position.y + size.y, position.z);
	m_Buffer->vertex = multiply(m_TransformationStack.back(), positions.size() > 0 ? positions[2] : glm::vec3(position.x + size.x, position.y + size.y, position.z));
	//m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
	m_Buffer->uv = uv[2];
	m_Buffer->tid = ts;
	m_Buffer->colour = color;
	++m_Buffer;

	//m_Buffer->vertex = positions[3];
	m_Buffer->vertex = multiply(m_TransformationStack.back(), positions.size() > 0 ? positions[3] : glm::vec3(position.x + size.x, position.y, position.z));
	//m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
	m_Buffer->uv = uv[3];
	m_Buffer->tid = ts;
	m_Buffer->colour = color;
	++m_Buffer;

	m_IndexCount += 6;
}

void BatchRenderer::drawString(const Font& font, const std::string& text, const glm::vec3& position, const glm::vec4& colour)
{
	using namespace ftgl;

	int r = colour.x * 255;
	int g = colour.y * 255;
	int b = colour.z * 255;
	int a = colour.w * 255;

	unsigned int color = a << 24 | b << 16 | g << 8 | r;

	float ts = 0.0f;
	bool found = false;

	for (int i = 0; i < m_TextureSlots.size(); ++i)
	{
		if (m_TextureSlots[i] == font.getID())
		{
			ts = (float)(i + 1);
			found = true;
			break;
		}
	}

	if (!found)
	{
		if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES)
		{
			end();
			flush();
			begin();
		}
		m_TextureSlots.push_back(font.getID());
		ts = (float)(m_TextureSlots.size());
	}

	float x = position.x;

	texture_font_t* ftFont = font.getFTFont();

	for (int i = 0; i < text.length(); i++)
	{
		char c = text.at(i);
		texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
		
		if (glyph != NULL)
		{
			if (i > 0)
			{
				float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
				x += kerning;
			}


			float x0 = x + glyph->offset_x;
			float y0 = position.y + glyph->offset_y;
			float x1 = x0 + glyph->width;
			float y1 = y0 - glyph->height;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			m_Buffer->vertex = glm::vec3(x0, y0, 0);
			m_Buffer->uv = glm::vec2(u0, v0);
			m_Buffer->tid = ts;
			m_Buffer->colour = color;
			++m_Buffer;

			m_Buffer->vertex = glm::vec3(x0, y1, 0);
			m_Buffer->uv = glm::vec2(u0, v1);
			m_Buffer->tid = ts;
			m_Buffer->colour = color;
			++m_Buffer;

			m_Buffer->vertex = glm::vec3(x1, y1, 0);
			m_Buffer->uv = glm::vec2(u1, v1);
			m_Buffer->tid = ts;
			m_Buffer->colour = color;
			++m_Buffer;

			m_Buffer->vertex = glm::vec3(x1, y0, 0);
			m_Buffer->uv = glm::vec2(u1, v0);
			m_Buffer->tid = ts;
			m_Buffer->colour = color;
			++m_Buffer;

			m_IndexCount += 6;

			x += glyph->advance_x;
		}
	}
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
	//glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < m_TextureSlots.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
	}

	glBindVertexArray(m_VAO);
	m_IBO->bind();

	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBlendFunc(GL_ONE, GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	m_IBO->unbind();
	glBindVertexArray(0);

	m_IndexCount = 0;
	m_TextureSlots.clear();
}

glm::vec3 BatchRenderer::multiply(const glm::mat4 & matrix, const glm::vec3 vector)
{
	return glm::vec3(
		matrix[0].x * vector.x + matrix[0].y * vector.y + matrix[0].z * vector.z + matrix[0].w,
		matrix[1].x * vector.x + matrix[1].y * vector.y + matrix[1].z * vector.z + matrix[1].w,
		matrix[2].x * vector.x + matrix[2].y * vector.y + matrix[2].z * vector.z + matrix[2].w
		);
}

