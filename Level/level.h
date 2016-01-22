#pragma once

#include "../Graphics/Layers/layer.h"
#include <glm\matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../Graphics/window.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "../Entity/entity.h"
#include "../Entity/player.h"
#include "../Entity/particle.h"
#include "../Entity/platform.h"
#include "zone.h"

#include "../Utils/quadTree.h"

class Player;

class Level
{
public:
	Level(Window& window);

	void update();
	void render();

	void addParticle(Entity* particle);
	void addPlatform(Entity* platform);
	void addProjectile(Entity* projectile);
	void addPlatform(Renderable* platform);

	void moveCamera(const float& x, const float& y);
	
	GLFWwindow* getWindow() { return m_Window.getWindow(); }
	Window& getWindowClass() { return m_Window; }
	Layer& getLayer() { return *m_Layer; }
	std::vector<Entity*>& getPlatforms() { return m_Platforms; }
	std::vector<Renderable*> getPlatform() { return m_Platform; }
	glm::vec2& getOffset() { return m_Offset; }

private:
	Layer* m_Layer;
	Shader* m_Shader;
	Window& m_Window;

	Player* m_Player;

	glm::mat4 m_Ortho;
	glm::vec2 m_Offset;

	std::vector<Entity*> m_Particles;
	std::vector<Entity*> m_Platforms;
	std::vector<Renderable*> m_Platform;
	std::vector<Entity*> m_Projectiles;

	QuadTree* quad;

};