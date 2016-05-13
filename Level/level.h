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
#include "../Entity/Mobs/enemy.h"
#include "../Entity/particle.h"
#include "../Entity/platform.h"
#include "zone.h"

#include "../Utils/quadTree.h"
#include "../Graphics/texture_manager.h"

#include "../Graphics/label.h"
#include "../Graphics/font_manager.h"
#include "../Entity/damage_counter.h"
#include "../Utils/perlinNoise.h"

class Player;
class Enemy;

class Level
{
public:
	Level(Window& window);

	void update(float timeElapsed);
	void render();

	void addParticle(Entity* particle);
	void addPlatform(Entity* platform);
	void addProjectile(Entity* projectile);
	void addPlatform(Renderable* platform);
	void addBlock(float x, float y);
	void addEnemy(const int& x, const int& y, const int& size);
	void addDamageText(const std::string& text, const int& x, const int& y);

	void moveCamera(const float& x, const float& y);
	
	GLFWwindow* getWindow() { return m_Window.getWindow(); }
	Window& getWindowClass() { return m_Window; }
	Layer& getLayer() { return *m_Layer; }
	std::vector<Renderable*> getPlatform() { return m_Platform; }
	const std::vector<std::unique_ptr<Enemy>>& getEnemies() { return m_Enemies; }
	glm::vec2& getOffset() { return m_Offset; }
	const std::unique_ptr<QuadTree>& getQuadTree() { return quad; }

	//const float playerX() { return m_Player->getCenterX(); }
	//const float playerY() { return m_Player->getCenterY(); }

private:
	Layer* m_Layer;
	Shader m_Shader;
	Window& m_Window;

	std::unique_ptr<Player> m_Player;

	glm::mat4 m_Ortho;
	glm::vec2 m_Offset;

	std::vector<Entity*> m_Particles;
	std::vector<Renderable*> m_Platform;
	std::vector<Entity*> m_Projectiles;

	std::unique_ptr<QuadTree> quad;

	Sprite* Background;
	std::unique_ptr<Label> m_Label;

	std::vector<std::unique_ptr<Enemy>> m_Enemies;
	std::vector<std::unique_ptr<DamageCounter>> m_DamageTexts;

};