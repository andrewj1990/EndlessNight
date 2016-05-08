#pragma once

#include "../entity.h"

class Enemy : public Entity
{
public:
	Enemy(const int& x, const int& y, const int& size, Level& level);

	void update() override;
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
	float m_Size;
	float m_Dx;
	float m_Dy;
	float m_Health;

};