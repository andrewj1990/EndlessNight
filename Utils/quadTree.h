#pragma once

#include <vector>
#include "../Graphics/renderable.h"

struct BoundingBox
{
	int x;
	int y;
	int width;
	int height;

	BoundingBox(int x, int y, int width, int height)
		: x(x), y(y), width(width), height(height)
	{ }

	bool contains(Renderable data)
	{
		bool containsX = (x <= data.getPosition().x && data.getPosition().x <= x + width);
		bool containsY = (y <= data.getPosition().y && data.getPosition().y <= y + height);

		return (containsX && containsY);
	}

	bool intersects(Renderable box)
	{
		return (x <= box.getPosition().x + box.getSize().x && x + width >= box.getPosition().x && y <= box.getPosition().y + box.getSize().y && y + height >= box.getPosition().y);
	}
};

class QuadTree
{
public:
	QuadTree(int level, BoundingBox bounds);
	~QuadTree();

	void clear();
	void split();

	void retrieve(std::vector<Renderable*>& list, Renderable range);
	bool insert(Renderable* data);

	void getBounds(std::vector<BoundingBox>& bounds);

	int getIndex(BoundingBox rect);

private:
	int max_objects;
	int max_levels;

	int m_Level;
	std::vector<Renderable*> m_Objects;
	BoundingBox m_Bounds;
	QuadTree* ne;
	QuadTree* se;
	QuadTree* sw;
	QuadTree* nw;

};