#include "level.h"
#include "../Graphics/label.h"
#include "../Graphics/font.h"
#include "../Graphics/font_manager.h"

Level::Level(Window& window)
	: m_Window(window), m_Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag")
{
	SpriteSheet* spritesheet = new SpriteSheet("Textures/spritesheetTest.png");
	SpriteSheet* platforms_spritesheet = new SpriteSheet("Textures/Platforms.png");
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/Top.png"				, 1, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/Right.png"			, 2, 1, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/Bottom.png"			, 1, 2, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/Left.png"				, 0, 1, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopRight.png"			, 2, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopBottom.png"		, 4, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopLeft.png"			, 0, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/RightLeft.png"		, 3, 2, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/BottomRight.png"		, 2, 2, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/BottomLeft.png"		, 0, 2, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/All.png"				, 4, 2, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopRightLeft.png"		, 3, 1, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopBottomRight.png"	, 5, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/BottomRightLeft.png"	, 4, 1, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/TopBottomLeft.png"	, 3, 0, 32, 32));
	TextureManager::add(new Texture(*platforms_spritesheet, "Textures/None.png"				, 1, 1, 32, 32));


	// TEXTURES //
	//TextureManager::add(new Texture("Textures/Top.png"));
	//TextureManager::add(new Texture("Textures/Right.png"));
	//TextureManager::add(new Texture("Textures/Bottom.png"));
	//TextureManager::add(new Texture("Textures/Left.png"));
	//TextureManager::add(new Texture("Textures/TopRight.png"));
	//TextureManager::add(new Texture("Textures/TopBottom.png"));
	//TextureManager::add(new Texture("Textures/TopLeft.png"));
	//TextureManager::add(new Texture("Textures/RightLeft.png"));
	//TextureManager::add(new Texture("Textures/BottomRight.png"));
	//TextureManager::add(new Texture("Textures/BottomLeft.png"));
	//TextureManager::add(new Texture("Textures/All.png"));
	//TextureManager::add(new Texture("Textures/TopRightLeft.png"));
	//TextureManager::add(new Texture("Textures/TopBottomRight.png"));
	//TextureManager::add(new Texture("Textures/BottomRightLeft.png"));
	//TextureManager::add(new Texture("Textures/TopBottomLeft.png"));
	//TextureManager::add(new Texture("Textures/None.png"));

	// FONTS //
	FontManager::add(new Font("Arial", "arial.ttf", 30));

	m_Offset = glm::vec2(0.0f, 0.0f);
	m_Ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	m_Layer = new Layer(m_Shader, m_Ortho);

	//Background = new Sprite(glm::vec3(0, 0, 0), glm::vec2(1200, 1000), new Texture("Textures/Background.png"));
	//m_Layer->add(Background);

	//Platform* platform = new Platform(m_Window.getWidth() / 3, 0, m_Window.getWidth() / 2, m_Window.getHeight() / 2, *this);
	//m_Platforms.push_back(platform);
	m_Player = std::unique_ptr<Player>(new Player(m_Window.getWidth() / 2 - 5, m_Window.getHeight() / 2 - 5, *this));

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

	//Platform* test = new Platform(*this);

	m_Label = std::unique_ptr<Label>(new Label("Altitude : ", 0, 0, FontManager::get("Arial"), glm::vec4(1, 1, 1, 1)));
	m_Layer->add(m_Label.get());

	//addPlatform(new Renderable(glm::vec3(0, 0, 1), glm::vec2(window.getWidth()), glm::vec4(0,0,0,1)));

	//m_Enemies.push_back(std::unique_ptr<Enemy>(new Enemy(50, 50, *this)));
	addEnemy(50, 50, 50);
}

void Level::update(float elapsedTime)
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

	for (const auto& enemy : m_Enemies)
	{
		quad->insert(enemy->getSprite());
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

	for (auto i = m_Enemies.begin(); i != m_Enemies.end(); )
	{
		if ((*i)->shouldDestroy())
		{
			m_Layer->remove((*i)->getSprite());
			i = m_Enemies.erase(i);
		}
		else
		{
			(*i)->update();
			++i;
		}
	}

	for (auto i = m_DamageTexts.begin(); i != m_DamageTexts.end(); )
	{
		m_Layer->remove((*i)->getLabel().get());
		m_Layer->add((*i)->getLabel().get());

		if ((*i)->shouldDestroy())
		{
			m_Layer->remove((*i)->getLabel().get());
			i = m_DamageTexts.erase(i);
		}
		else
		{
			(*i)->update();
			++i;
		}

	}

	m_Label->text = "Altitude : " + std::to_string(m_Offset.y);
}

void Level::render()
{
	m_Label->position.x = m_Offset.x + 15;
	m_Label->position.y = m_Offset.y + m_Window.getHeight() - 45;
	m_Shader.setUniform2f("light_pos", glm::vec2(m_Player->getCenterX(), m_Player->getCenterY()));
	m_Layer->render();
}

void Level::addParticle(Entity* particle)
{
	m_Particles.push_back(particle);
//	m_Layer->add(particle->getSprite());
}

void Level::addBlock(float x, float y)
{
	Renderable* renderable = new Renderable(glm::vec3(x, y, 0), glm::vec2(50, 50), glm::vec4(0, 1, 1, 1));
	//m_Layer->add(new Renderable(glm::vec3(x, y, 0), glm::vec2(50, 50), glm::vec4(0, 1, 1, 1)));
	m_Layer->add(renderable);
	m_Platform.push_back(renderable);
	//m_Layer->add(new Block(x, y));
}

void Level::addPlatform(Renderable* platform)
{
	m_Platform.push_back(platform);
}

void Level::addProjectile(Entity* projectile)
{
	m_Projectiles.push_back(projectile);
}

void Level::addEnemy(const int& x, const int& y, const int& size)
{
	m_Enemies.push_back(std::unique_ptr<Enemy>(new Enemy(x, y, size, *m_Player, *this)));
}

void Level::addDamageText(const std::string& text, const int& x, const int& y)
{
	//std::unique_ptr<DamageCounter> damageText = std::unique_ptr<DamageCounter>(new DamageCounter(text, x, y));
	//m_DamageTexts.push_back(damageText);
	//m_Layer->add(damageText->getLabel().get());
	m_DamageTexts.push_back(std::unique_ptr<DamageCounter>(new DamageCounter(text, x, y)));
}

void Level::moveCamera(const float& x, const float& y)
{
	m_Offset.x += x;
	m_Offset.y += y;
	//std::cout << "offsetX : " << m_Offset.x << ", offsetY : " << m_Offset.y << "\n";

	m_Ortho = glm::translate(m_Ortho, glm::vec3(-x, -y, 0));
	m_Layer->setProjectionMatrix(m_Ortho);
}