#pragma once

#include "sprite.h"
#include <vector>

class Level;

class Entity
{
public:
	Entity(int x, int y, Level& level);
	virtual ~Entity() { delete m_Sprite; }

	virtual void update(float timeElapsed);
	virtual void render();

	virtual bool collision();

	inline const float& getX() const { return m_X; }
	inline const float& getY() const { return m_Y; }
	inline const int getCenterX() const { return (m_X + (m_Width / 2)); }
	inline const int getCenterY() const { return (m_Y + (m_Height / 2)); }
	inline const int& getWidth() const { return m_Width; }
	inline const int& getHeight() const { return m_Height; }

	bool shouldDestroy() const { return m_Destroy; }
	Sprite* getSprite() const { return m_Sprite; }

protected:
	void addToLevel(Renderable* renderable);

protected:
	float m_X;
	float m_Y;
	int m_Width;
	int m_Height;

	Level& m_Level;
	Sprite* m_Sprite;

	bool m_Destroy;

private:

};

#include "../Level/level.h"