#pragma once

#include <cstdlib>
#include "entity.h"
#include <queue>
#include <unordered_map>
#include "../Graphics/texture_manager.h"
#include "../Utils/Node.h"
#include "../Level/level.h"

class Platform : public Entity
{
public:
	Platform(Level& level);
	Platform(int x, int y, int width, int height, Level& level);
	
	void update() override;
	void render() override;

private:
	void generatePlatforms(int x, int y);
	void setTextures();

private:
	Texture* tex;
	std::vector<Sprite*> m_Sprites;
	std::queue<Node> m_Queue;
	int m_Size;

	std::unordered_map<int, bool> visited;

};