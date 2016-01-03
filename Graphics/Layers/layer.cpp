#include "layer.h"

Layer::Layer(Shader* shader, const glm::mat4 projectionMatrix)
	: m_ProjectionMatrix(projectionMatrix), m_Shader(shader)
{
	m_Renderer = new BatchRenderer();	

	m_Shader->bind();
	m_Shader->setUniformMat4("pr_matrix", projectionMatrix);
	m_Shader->unbind();
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

//	for (int i = 0; i < m_Renderables.size(); ++i)
//	{
//		if (m_Renderables[i] == ptr)
//		{
////			delete *i;
//			m_Renderables.erase(m_Renderables.begin() + i);
//			return;
//		}
//	}
}

void Layer::render()
{
	m_Shader->bind();

//	std::cout << "renderables size : " << m_Renderables.size() << "\n";

	m_Renderer->begin();
	for (Renderable* renderable : m_Renderables)
	{
		m_Renderer->submit(*renderable);
	}
	m_Renderer->end();
	m_Renderer->flush();

}

void Layer::setProjectionMatrix(const glm::mat4 projectionMatrix)
{
	m_Shader->bind();
	m_Shader->setUniformMat4("pr_matrix", projectionMatrix);
	m_Shader->unbind();
}