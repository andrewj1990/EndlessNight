#include "astar.h"

int heuristic(const Node& a, const Node& b)
{
	const int& x1 = a.x;
	const int& y1 = a.y;
	const int& x2 = b.x;
	const int& y2 = b.y;

	return abs(x1 - x2) + abs(y1 - y2);
}

int cost(const Node& node, const std::unique_ptr<QuadTree>& qt)
{
	std::vector<Renderable*> platforms;
	qt->retrieve(platforms, node.x, node.y, 0, 0);
	for (Renderable* platform : platforms)
	{
		const int& px = platform->getPosition().x;
		const int& py = platform->getPosition().y;
		const int& w = platform->getSize().x;
		const int& h = platform->getSize().y;

		if (node.x <= px + w && node.x >= px && node.y >= py && node.y<= py + h)
		{
			return 200;
		}
	}

	return 1;
	//return (rand() % 10);
}

std::unordered_map<int, Node> bfsSearch(int x, int y, glm::vec2 end)
{
	Node node(x, y);
	std::queue<Node> frontier;
	frontier.push(node);

	Node endNode(end.x, end.y);
	
	std::unordered_map<int, Node> came_from;

	came_from[node.getInt()] = node;

	while (!frontier.empty())
	{
		Node current = frontier.front();
		frontier.pop();

		if (current.getInt() == endNode.getInt()) return came_from;
		// if already visited then continue
		for (Node next : current.neighbors())
		{
			// if already visited then continue
			if (!came_from.count(next.getInt()))
			{
				frontier.push(next);
				came_from[next.getInt()] = current;
			}

		}
	}

	return came_from;

}

std::unordered_map<int, Node> aStarSearch(int x, int y, glm::vec2 end, const std::unique_ptr<QuadTree>& qt)
{
	Node node(x, y);
	typedef std::pair<int, Node> PQElement;
	//std::priority_queue<Node> frontier;
	std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
	//frontier.push(node);
	frontier.emplace(0, node);
	Node goal(end.x, end.y);

	std::unordered_map<int, Node> came_from;
	std::unordered_map<int, int> cost_so_far;

	came_from[node.getInt()] = node;
	cost_so_far[node.getInt()] = 0;

	while (!frontier.empty())
	{
		Node current = frontier.top().second;
		frontier.pop();

		if (current.getInt() == goal.getInt()) return came_from;
		// if already visited then continue
		for (Node next : current.neighbors())
		{
			int new_cost = cost_so_far[current.getInt()] + cost(next, qt);
			// if already visited then continue
			if (!came_from.count(next.getInt()) || new_cost < cost_so_far[next.getInt()])
			{
				cost_so_far[next.getInt()] = new_cost;
				int priority = new_cost + heuristic(next, goal);
				frontier.emplace(priority, next);
				came_from[next.getInt()] = current;
			}

		}
	}

	return came_from;

}