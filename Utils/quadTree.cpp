#include "quadTree.h"

QuadTree::QuadTree(int level, BoundingBox bounds)
	: m_Level(level), m_Bounds(bounds), ne(nullptr), se(nullptr), sw(nullptr), nw(nullptr)
{
	max_objects = 2;
	//max_levels = 10;
}

QuadTree::~QuadTree()
{
	delete se;
	delete ne;
	delete sw;
	delete nw;
}

void QuadTree::split()
{
	int subWidth = m_Bounds.width / 2;
	int subHeight = m_Bounds.height / 2;
	int x = m_Bounds.x;
	int y = m_Bounds.y;

	se = new QuadTree(m_Level + 1, BoundingBox(x, y, subWidth, subHeight));
	ne = new QuadTree(m_Level + 1, BoundingBox(x + subWidth, y, subWidth, subHeight));
	sw = new QuadTree(m_Level + 1, BoundingBox(x, y + subHeight, subWidth, subHeight));
	nw = new QuadTree(m_Level + 1, BoundingBox(x + subWidth, y + subHeight, subWidth, subHeight));
}

int QuadTree::getIndex(BoundingBox rect)
{
	int index = -1;
	float vertMidpoint = m_Bounds.x + (m_Bounds.width / 2.0f);
	float horiMidpoint = m_Bounds.y + (m_Bounds.height / 2.0f);

	bool topQuad = (rect.y < horiMidpoint && rect.y + rect.height < horiMidpoint);
	bool botQuad = (rect.y > horiMidpoint);

	if (rect.x < vertMidpoint && rect.x + rect.width < vertMidpoint)
	{
		if (topQuad)
		{
			index = 1;
		}
		else if (botQuad)
		{
			index = 2;
		}
	}
	else if (rect.x > vertMidpoint)
	{
		if (topQuad) {
			index = 0;
		}
		else if (botQuad)
		{
			index = 3;
		}
	}

	return index;
}

bool QuadTree::insert(Renderable* data)
{
	if (!m_Bounds.contains(*data))
	{
		return false;
	}

	if (m_Objects.size() < max_objects)
	{
		m_Objects.push_back(data);
		return true;
	}

	if (nw == nullptr)
	{
		split();
	}

	if (nw->insert(data)) return true;
	if (ne->insert(data)) return true;
	if (sw->insert(data)) return true;
	if (se->insert(data)) return true;

	return false;
}

void QuadTree::retrieve(std::vector<Renderable*>& data, Renderable range)
{
	if (!m_Bounds.intersects(range))
	{
		return;
	}

	for (Renderable* object : m_Objects)
	{
		if (m_Bounds.contains(*object))
		{
			data.push_back(object);
		}
	}

	if (nw == nullptr) return;

	nw->retrieve(data, range);
	ne->retrieve(data, range);
	sw->retrieve(data, range);
	se->retrieve(data, range);

}

void QuadTree::getBounds(std::vector<BoundingBox>& bounds)
{
	bounds.push_back(m_Bounds);

	if (nw == nullptr) return;

	nw->getBounds(bounds);
	ne->getBounds(bounds);
	sw->getBounds(bounds);
	se->getBounds(bounds);

}