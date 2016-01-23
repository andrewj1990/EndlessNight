#pragma once

#include <vector>
#include "../../Utils/shader.h"
#include "../renderable.h"
#include "../batchrenderer.h"

#include <iostream>


class Layer
{
public:
	Layer(Shader& shader, const glm::mat4 projectionMatrix);

	void add(Renderable* renderable);
	void remove(Renderable* ptr);

	void render();
	void render(std::vector<Renderable*> renderables);

	void setProjectionMatrix(const glm::mat4 projectionMatrix);
	glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }
	const std::vector<Renderable*>& getRenderables() const { return m_Renderables; }

private:
	BatchRenderer m_Renderer;
	Shader& m_Shader;
	const glm::mat4& m_ProjectionMatrix;
	std::vector<Renderable*> m_Renderables;
};