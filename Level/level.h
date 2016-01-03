#pragma once

#include "../Graphics/Layers/layer.h"
#include <glm\matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../Graphics/window.h"

#include <algorithm>
#include <iterator>

#include "../Entity/player.h"
#include "../Entity/particle.h"
#include "../Entity/platform.h"
#include "zone.h"

class Player;

class Level
{
public:
	Level(Window& window);

	void update();
	void render();

	void addParticle(Particle* particle);
	void addPlatform(Platform* platform);

	void moveCamera(const float& x, const float& y);
	
	std::vector<Platform*>& getPlatforms() { return m_Platforms; }


private:
	Layer* m_Layer;
	Shader* m_Shader;
	Window& m_Window;

	Player* m_Player;

	glm::mat4 m_Ortho;
	glm::vec2 m_Offset;

	std::vector<Particle*> m_Particles;
	std::vector<Platform*> m_Platforms;

};