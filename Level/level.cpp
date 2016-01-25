#include "level.h"
#include "../Graphics/label.h"
#include "../Graphics/font.h"
#include "../Graphics/font_manager.h"

Level::Level(Window& window)
	: m_Window(window), m_Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag")
{
	// TEXTURES //
	TextureManager::add(new Texture("Textures/Top.png"));
	TextureManager::add(new Texture("Textures/Right.png"));
	TextureManager::add(new Texture("Textures/Bottom.png"));
	TextureManager::add(new Texture("Textures/Left.png"));
	TextureManager::add(new Texture("Textures/TopRight.png"));
	TextureManager::add(new Texture("Textures/TopBottom.png"));
	TextureManager::add(new Texture("Textures/TopLeft.png"));
	TextureManager::add(new Texture("Textures/RightLeft.png"));
	TextureManager::add(new Texture("Textures/BottomRight.png"));
	TextureManager::add(new Texture("Textures/BottomLeft.png"));
	TextureManager::add(new Texture("Textures/All.png"));
	TextureManager::add(new Texture("Textures/TopRightLeft.png"));
	TextureManager::add(new Texture("Textures/TopBottomRight.png"));
	TextureManager::add(new Texture("Textures/BottomRightLeft.png"));
	TextureManager::add(new Texture("Textures/TopBottomLeft.png"));
	TextureManager::add(new Texture("Textures/None.png"));

	// FONTS //
	FontManager::add(new Font("blah", "LuckiestGuy.ttf", 80));

	m_Offset = glm::vec2(0.0f, 0.0f);
	m_Ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	m_Layer = new Layer(m_Shader, m_Ortho);

	Background = new Sprite(glm::vec3(0, 0, 0), glm::vec2(1280, 1000), new Texture("Textures/Background.png"));
	//m_Layer->add(Background);

	//Platform* platform = new Platform(m_Window.getWidth() / 3, 0, m_Window.getWidth() / 2, m_Window.getHeight() / 2, *this);
	//m_Platforms.push_back(platform);
	m_Player = std::unique_ptr<Player>(new Player(m_Window.getWidth() / 2, m_Window.getHeight() / 2, *this));

	int center = 0;
	int center_width = 1280;
	int center_height = 720;

	//Zone* zone1 = new Zone(1280, 720, m_Window, *m_Layer, *this);
	//Zone* zone2 = new Zone(1280, 0, m_Window, *m_Layer, *this);
	//Zone* zone3 = new Zone(1280, -720, m_Window, *m_Layer, *this);
	//Zone* zone4 = new Zone(0, 720, m_Window, *m_Layer, *this);
	//Zone* zone5 = new Zone(0, 0, m_Window, *m_Layer, *this);
	//Zone* zone6 = new Zone(0, -720, m_Window, *m_Layer, *this);
	//Zone* zone7 = new Zone(-1280, 720, m_Window, *m_Layer, *this);
	//Zone* zone8 = new Zone(-1280, 0, m_Window, *m_Layer, *this);
	//Zone* zone9 = new Zone(-1280, -720, m_Window, *m_Layer, *this);

	Platform* test = new Platform(*this);

}

std::vector<Renderable*> boxes;
std::vector<BoundingBox> bounds;
void Level::update()
{
	double x;
	double y;
	m_Window.getMousePos(x, y);
	x += m_Offset.x;
	y += m_Offset.y;

	quad = std::unique_ptr<QuadTree>(new QuadTree(0, BoundingBox(m_Offset.x, m_Offset.y, 1280, 720)));
	for (Renderable* r : m_Platform)
	{
		quad->insert(r);
	}


	m_Player->update();

	// check if any particles need to be deleted
	for (auto i = m_Particles.begin(); i != m_Particles.end(); )
	{
		if ((*i)->shouldDestroy())
		{
			m_Layer->remove((*i)->getSprite());
			delete *i;
			i = m_Particles.erase(i);
		}
		else
		{
			(*i)->update();
			++i;
		}
	}

	for (auto i = m_Projectiles.begin(); i != m_Projectiles.end(); )
	{
		if ((*i)->shouldDestroy())
		{
			m_Layer->remove((*i)->getSprite());
			delete *i;
			i = m_Projectiles.erase(i);
		}
		else
		{
			(*i)->update();
			++i;
		}
	}

	//std::vector<Renderable*> list;
	//quad->retrieve(list, *m_Player->getSprite());
	//std::cout << " list size : " << list.size() << "\n";
	//boxes.clear();
	//bounds.clear();
	//quad->getBounds(bounds);
}

void Level::render()
{
	//int size = 1;
	//for (const BoundingBox& b : bounds)
	//{
	//	boxes.push_back(new Sprite(glm::vec3(b.x, b.y, 0), glm::vec2(b.width, size), glm::vec4(1, 1, 0, 1)));
	//	boxes.push_back(new Sprite(glm::vec3(b.x, b.y, 0), glm::vec2(size, b.height), glm::vec4(1, 1, 0, 1)));
	//	boxes.push_back(new Sprite(glm::vec3(b.x + b.width, b.y, 0), glm::vec2(size, b.height), glm::vec4(1, 1, 0, 1)));
	//	boxes.push_back(new Sprite(glm::vec3(b.x, b.y + b.height, 0), glm::vec2(b.width, size), glm::vec4(1, 1, 0, 1)));
	//}
	//m_Layer->render(boxes);
	m_Shader.setUniform2f("light_pos", glm::vec2(m_Player->getCenterX(), m_Player->getCenterY()));
	m_Layer->render();
}

void Level::addParticle(Entity* particle)
{
	m_Particles.push_back(particle);
//	m_Layer->add(particle->getSprite());
}

void Level::addPlatform(Renderable* platform)
{
	m_Platform.push_back(platform);
}

void Level::addPlatform(Entity* platform)
{
	m_Platforms.push_back(platform);
}

void Level::addProjectile(Entity* projectile)
{
	m_Projectiles.push_back(projectile);
}

void Level::moveCamera(const float& x, const float& y)
{
	m_Offset.x += x;
	m_Offset.y += y;
	//std::cout << "offsetX : " << m_Offset.x << ", offsetY : " << m_Offset.y << "\n";

	m_Ortho = glm::translate(m_Ortho, glm::vec3(-x, -y, 0));
	m_Layer->setProjectionMatrix(m_Ortho);
}