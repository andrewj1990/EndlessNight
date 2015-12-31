#pragma once

#include <vector>
#include "../../Utils/shader.h"
#include "../renderable.h"
#include "../batchrenderer.h"

#include <iostream>

class Layer
{
public:
	Layer(Shader* shader, const glm::mat4 projectionMatrix);

	void add(Renderable* renderable);
	void render();

private:
	BatchRenderer* m_Renderer;
	Shader* m_Shader;
	const glm::mat4& m_ProjectionMatrix;
	std::vector<Renderable*> m_Renderables;
};