#pragma once

#include <cstdlib>
#include "entity.h"

class Platform : public Entity
{
public:
	Platform(Level& level);
	Platform(int x, int y, int width, int height, Level& level);
	
	void update() override;
	void render() override;

private:

};