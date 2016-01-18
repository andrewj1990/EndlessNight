#include "platform.h"

Platform::Platform(Level& level)
	: Entity(0, 0, level)
{
	//m_X = rand() % 1280;
	//m_Y = rand() % 720;
	//m_Width = 100 + (rand() % 100);
	//m_Height = 100 + (rand() % 100);
	//tex = new Texture("test.png");
	////m_Sprite = new Sprite(glm::vec3(100, 100, 0), glm::vec2(m_Width, m_Height), tex);

	//m_Sprite = new Sprite(glm::vec3(100, 100, 0), glm::vec2(100, 100), glm::vec4(rand() % 1000 / 1000.0f, 0, 0, 1));
	//addToLevel(m_Sprite);


	generatePlatforms(500, 500);
	generatePlatforms(100, 100);
	generatePlatforms(900, 500);

	setTextures();
	for (Sprite* sprite : m_Sprites)
	{
		addToLevel(sprite);
	}

}

Platform::Platform(int x, int y, int width, int height, Level& level)
	: Entity(x, y, level)
{
	m_Width = width;
	m_Height = height;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 0, 1));
	//tex = new Texture("test.png");
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(m_Width, m_Height), tex);

	addToLevel(m_Sprite);
}

void Platform::generatePlatforms(int x, int y)
{
	int size = 10;
	const int& width = m_Level.getWindowClass().getWidth();
	const int& height = m_Level.getWindowClass().getHeight();
	
	m_Queue.push(Node(x, y));

	int counter = 0;
	while (m_Queue.size() > 0)
	{
		if (counter > 1000) break;
		Node currentNode = m_Queue.front();
		int xx = currentNode.x;
		int yy = currentNode.y;
		
		const int& index = xx + yy * width;

		auto isVisited = visited.find(index);

		// key was not found which means node has not been visited yet
		if (isVisited == visited.end())
		{
			visited.insert({ index, false });
			if ((rand() % 10) < 7)
			{
				visited[index] = true;
				m_Sprites.push_back(new Sprite(glm::vec3(xx, yy, 0), glm::vec2(size, size), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 0, 1)));
				m_Queue.push(Node(xx + size, yy));
				m_Queue.push(Node(xx, yy + size));
				m_Queue.push(Node(xx - size, yy));
				m_Queue.push(Node(xx, yy - size));
			}
		
		} 
		else
		{
			m_Queue.pop();
		}

		counter++;
	}

	m_Queue = std::queue<Node>();
	counter = 0;
}

void Platform::setTextures()
{
	for (Sprite* sprite : m_Sprites)
	{
		const int& x = sprite->getPosition().x;
		const int& y = sprite->getPosition().y;

		const int& width = m_Level.getWindowClass().getWidth();
		const int& height = m_Level.getWindowClass().getHeight();

		const int& size = 10;

		auto isVisitedTop = visited.find((x) + (y + size) * width);
		auto isVisitedRight = visited.find((x + size) + (y) * width);
		auto isVisitedDown = visited.find((x) + (y - size) * width);
		auto isVisitedLeft = visited.find((x - size) + (y) * width);

		if (isVisitedLeft == visited.end() || isVisitedLeft->second == false)
		{
			sprite->setColor(1, 1, 1);
		}

		if (isVisitedTop == visited.end() || isVisitedTop->second == false)
		{
			sprite->setColor(0, 0, 1);
		}

	}

}

void Platform::update()
{

}

void Platform::render()
{

}