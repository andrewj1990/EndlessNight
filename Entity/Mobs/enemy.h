#pragma once

#include "../entity.h"
#include "../player.h"

class Player;

class Enemy : public Entity
{
public:
	Enemy(const int& x, const int& y, const int& size, const Player& player, Level& level);

	void update(float timeElapsed) override;
	void render() override;

	const int& getX() { return m_X; }
	const int& getY() { return m_Y; }
	const int& getSize() { return m_Size; }

	void setDestroy(bool destroy) { m_Destroy = destroy; }
	void damage(float amount);

private:
	void move(const double& dx, const double& dy);
	bool collision(int x, int y);

private:
	const Player& m_Player;

	float m_Dx;
	float m_Dy;

	float m_Pdx;
	float m_Pdy;
	float prevX;
	float prevY;
	int count;

	float m_Angle;
	float m_PlayerAngle;

	float m_Size;
	float m_Health;

};