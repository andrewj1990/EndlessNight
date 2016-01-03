#pragma once

#include "sprite.h"

class Level;

class Entity
{
public:
	Entity(int x, int y, Level& level);
	virtual ~Entity() {}

	virtual void update();
	virtual void render();


	inline const int& getX() const { return m_X; }
	inline const int& getY() const { return m_Y; }
	inline const int& getWidth() const { return m_Width; }
	inline const int& getHeight() const { return m_Height; }

	bool shouldDestroy() const { return m_Destroy; }
	Sprite* getSprite() const { return m_Sprite; }

protected:
	void addToLevel(Renderable* renderable);

protected:
	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;

	Level& m_Level;
	Sprite* m_Sprite;

	bool m_Destroy;

private:

};

#include "../Level/level.h"