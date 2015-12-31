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

void Layer::render()
{
	m_Shader->bind();

	m_Renderer->begin();
	for (Renderable* renderable : m_Renderables)
	{
		m_Renderer->submit(*renderable);
	}
	m_Renderer->end();
	m_Renderer->flush();

}