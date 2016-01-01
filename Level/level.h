#pragma once

#include "../Graphics/Layers/layer.h"
#include <glm\matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../Graphics/window.h"

#include "../Entity/player.h"
#include "../Entity/particle.h"

class Level
{
public:
	Level(Window& window);

	void update();
	void render();

private:
	Layer* m_Layer;
	Shader* m_Shader;
	Window m_Window;

	Player* m_Player;

	std::vector<Particle*> m_Particles;

	float ox;
	float oy;

};