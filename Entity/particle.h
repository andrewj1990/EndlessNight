#pragma once

#include <vector>
#include "sprite.h"
#include "../Graphics/Layers/layer.h"
#include <ctime>

class Particle
{
public:
	Particle(int x, int y, Layer& layer);
	Particle(int x, int y, Layer& layer, glm::vec4 colour);
	~Particle();

	void update();
	void render();
	bool shouldDestroy() const;

	Sprite* getSprite() const { return m_Sprite; }

private:
	int m_NumParticles;
	int m_Life;
	int m_TotalLife;
	float dx;
	float dy;

	bool m_Destroy;
	Sprite* m_Sprite;
	Layer& m_Layer;
};