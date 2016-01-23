#include "layer.h"

Layer::Layer(Shader& shader, const glm::mat4 projectionMatrix)
	: m_ProjectionMatrix(projectionMatrix), m_Shader(shader), m_Renderer()
{
	m_Shader.bind();
	m_Shader.setUniformMat4("pr_matrix", projectionMatrix);

	/*GLint texID[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};
*/
	GLint texID[32];
	for (int i = 0; i < 32; ++i)
	{
		texID[i] = i;
	}


	m_Shader.setUniform1iv("textures", 32, texID);
	m_Shader.unbind();
}

void Layer::add(Renderable* renderable)
{
	m_Renderables.push_back(renderable);
}

void Layer::remove(Renderable* ptr)
{
	for (int i = m_Renderables.size() - 1; i >= 0; --i)
	{
		if (m_Renderables[i] == ptr)
		{
			m_Renderables.erase(m_Renderables.begin() + i);
			return;
		}
	}
}

void Layer::render()
{
	m_Shader.bind();

	//std::cout << "renderables size : " << m_Renderables.size() << "\n";

	m_Renderer.begin();
	for (Renderable* renderable : m_Renderables)
	{
		//m_Renderer->submit(*renderable);
		renderable->submit(m_Renderer);
	}

//	m_Renderer->drawString("hello", glm::vec3(100, 100, 0), glm::vec4(0, 1, 1, 1));

	m_Renderer.end();
	m_Renderer.flush();
}

void Layer::render(std::vector<Renderable*> renderables)
{
	m_Shader.bind();

	//	std::cout << "renderables size : " << m_Renderables.size() << "\n";

	m_Renderer.begin();
	for (Renderable* renderable : renderables)
	{
		m_Renderer.submit(*renderable);
	}
	m_Renderer.end();
	m_Renderer.flush();
}

void Layer::setProjectionMatrix(const glm::mat4 projectionMatrix)
{
	m_Shader.bind();
	m_Shader.setUniformMat4("pr_matrix", projectionMatrix);
	m_Shader.unbind();
}

