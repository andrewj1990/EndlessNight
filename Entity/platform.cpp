#include "platform.h"

Platform::Platform(Level& level)
	: Entity(0, 0, level), m_Size(30)
{
	//m_X = rand() % 1280;
	//m_Y = rand() % 720;
	//m_Width = 100 + (rand() % 100);
	//m_Height = 100 + (rand() % 100);
	//tex = new Texture("test.png");
	////m_Sprite = new Sprite(glm::vec3(100, 100, 0), glm::vec2(m_Width, m_Height), tex);

	//m_Sprite = new Sprite(glm::vec3(100, 100, 0), glm::vec2(100, 100), glm::vec4(rand() % 1000 / 1000.0f, 0, 0, 1));
	//addToLevel(m_Sprite);


	//generatePlatforms(500, 500);
	generatePlatforms(100, 100);
	generatePlatforms(900, 1000);


	//m_Sprites.push_back(new Sprite(glm::vec3(100, 500, 0), glm::vec2(30, 30), glm::vec4(1, 1, 0, 1)));
	//m_Sprites.push_back(new Sprite(glm::vec3(200, 500, 0), glm::vec2(30, 30), glm::vec4(1, 1, 0, 1)));
	//m_Sprites.push_back(new Sprite(glm::vec3(300, 500, 0), glm::vec2(30, 30), glm::vec4(1, 1, 0, 1)));
	//m_Sprites.push_back(new Sprite(glm::vec3(400, 500, 0), glm::vec2(30, 30), glm::vec4(1, 1, 0, 1)));
	//m_Sprites.push_back(new Sprite(glm::vec3(500, 500, 0), glm::vec2(30, 30), glm::vec4(1, 1, 0, 1)));

	//setTextures();
	for (Sprite* sprite : m_Sprites)
	{
		addToLevel(sprite);
		m_Level.addPlatform(sprite);
	}

}

Platform::Platform(int x, int y, int width, int height, Level& level)
	: Entity(x, y, level), m_Size(10)
{
	m_Width = width;
	m_Height = height;
	m_Sprite = new Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 0, 1));
	//tex = new Texture("test.png");
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(m_Width, m_Height), tex);

	addToLevel(m_Sprite);
	//m_Level.addPlatform(m_Sprite);
}

void Platform::generatePlatforms(int x, int y)
{
	const int& width = m_Level.getWindowClass().getWidth();
	const int& height = m_Level.getWindowClass().getHeight();
	
	m_Queue.push(Node(x, y));
	
	float greyColor = 8.0f / 255.0f;
	//float greyColor = 1;
	int counter = 0;
	while (m_Queue.size() > 0)
	{
		if (counter > 2000) break;
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
				//m_Sprites.push_back(new Sprite(glm::vec3(xx, yy, 0), glm::vec2(size, size), glm::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 0, 1)));
				m_Sprites.push_back(new Sprite(glm::vec3(xx, yy, 0), glm::vec2(m_Size, m_Size), glm::vec4(greyColor, greyColor, greyColor, 1)));
				//m_Sprites.push_back(new Sprite(glm::vec3(xx, yy, 0), glm::vec2(size, size), new Texture("test2.png")));
				m_Queue.push(Node(xx + m_Size, yy));
				m_Queue.push(Node(xx, yy + m_Size));
				m_Queue.push(Node(xx - m_Size, yy));
				m_Queue.push(Node(xx, yy - m_Size));
			}
		
		} 
		else
		{
			m_Queue.pop();
		}

		counter++;
	}

	// generate random background elements
	for (int i = 0; i < 100; ++i)
	{
		m_Sprites.push_back(new Sprite(glm::vec3(x + rand() % 1280, y + rand() % 720, 0), glm::vec2(m_Size, m_Size), glm::vec4(greyColor, greyColor, greyColor, 0.4f)));
	}

	m_Queue = std::queue<Node>();
	counter = 0;
}

void Platform::setTextures()
{
	int state = 0;
	for (Sprite* sprite : m_Sprites)
	{
		const int& x = sprite->getPosition().x;
		const int& y = sprite->getPosition().y;

		const int& width = m_Level.getWindowClass().getWidth();
		const int& height = m_Level.getWindowClass().getHeight();

		auto isVisitedTop = visited.find((x) + (y + m_Size) * width);
		auto isVisitedRight = visited.find((x + m_Size) + (y) * width);
		auto isVisitedDown = visited.find((x) + (y - m_Size) * width);
		auto isVisitedLeft = visited.find((x - m_Size) + (y) * width);

		state = 0;
		if (isVisitedTop == visited.end() || isVisitedTop->second == false)
		{
			state += 1;
		}
		if (isVisitedRight == visited.end() || isVisitedRight->second == false)
		{
			state += 3;
		}
		if (isVisitedDown == visited.end() || isVisitedDown->second == false)
		{
			state += 5;
		}
		if (isVisitedLeft == visited.end() || isVisitedLeft->second == false)
		{
			state += 11;
		}

		if (state == 1)		  sprite->setTexture(TextureManager::get("Textures/Top.png"));
		else if (state == 3)  sprite->setTexture(TextureManager::get("Textures/Right.png"));
		else if (state == 5)  sprite->setTexture(TextureManager::get("Textures/Bottom.png"));
		else if (state == 11) sprite->setTexture(TextureManager::get("Textures/Left.png"));
		else if (state == 4)  sprite->setTexture(TextureManager::get("Textures/TopRight.png"));
		else if (state == 6)  sprite->setTexture(TextureManager::get("Textures/TopBottom.png"));
		else if (state == 12) sprite->setTexture(TextureManager::get("Textures/TopLeft.png"));
		else if (state == 14) sprite->setTexture(TextureManager::get("Textures/RightLeft.png"));
		else if (state == 8)  sprite->setTexture(TextureManager::get("Textures/BottomRight.png"));
		else if (state == 16) sprite->setTexture(TextureManager::get("Textures/BottomLeft.png"));
		else if (state == 20) sprite->setTexture(TextureManager::get("Textures/All.png"));
		else if (state == 15) sprite->setTexture(TextureManager::get("Textures/TopRightLeft.png"));
		else if (state == 9)  sprite->setTexture(TextureManager::get("Textures/TopBottomRight.png"));
		else if (state == 19) sprite->setTexture(TextureManager::get("Textures/BottomRightLeft.png"));
		else if (state == 17) sprite->setTexture(TextureManager::get("Textures/TopBottomLeft.png"));
		else sprite->setTexture(TextureManager::get("Textures/None.png"));

	}

}

void Platform::update(float timeElapsed)
{

}

void Platform::render()
{

}