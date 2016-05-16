#include "level.h"
#include "../Graphics/label.h"
#include "../Graphics/font.h"
#include "../Graphics/font_manager.h"

Level::Level(Window& window)
	: m_Window(window), m_Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag"), m_BGMoved(false), m_TileSize(16)
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
	TextureManager::add(new Texture("Textures/Bullet.png"));
	TextureManager::add(new Texture("Textures/BulletGlow.png"));
	TextureManager::add(new Texture("Textures/Enemy.png"));
	TextureManager::add(new Texture("Textures/Top.png"));
	TextureManager::add(new Texture("Textures/PlayerSpritesheet10.png"));

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

	PerlinNoise testNoise;
	SimplexNoise testSimplex;
	double r = 0;
	double g = 0;
	double b = 0;
	for (int x = 0; x < window.getWidth() / m_TileSize; x++)
	{
		for (int y = 0; y < window.getHeight() / m_TileSize; y++)
		{
			//float val = testSimplex.octaveNoise(3, 0.5, 1, x, y);
			float val = m_Simplex.scaledOctaveNoise(5, 0.5, 1, 0, 1, x * 0.005f, y * 0.005f);
			//std::cout << val << "\n";
			//double val = testNoise.calcPerlinNoise(x, y);
			if (val < 0.3)
			{
				r = 0;
				g = 0;
				b = 0.4;
			}
			else if (val < 0.4)
			{
				r = 0;
				g = 0;
				b = 0.8;
			}
			else if (val < 0.5)
			{
				r = 0.5;
				g = 0.5;
				b = 0;
			}
			else if (val < 0.8)
			{
				r = 0;
				g = 0.4;
				b = 0;
			}
			else
			{
				r = 0.9;
				g = 0.9;
				b = 0.9;
			}

			Sprite* sprite = new Sprite(glm::vec3(x * m_TileSize, y * m_TileSize, 0), glm::vec2(m_TileSize, m_TileSize), glm::vec4(r, g, b, 1));
			std::string tile_pos = std::to_string(x) + "_" + std::to_string(y);
			m_BackgroundTiles[tile_pos] = sprite;
			m_Layer->add(sprite);
			//m_Layer->add(new Sprite(glm::vec3(x * tile_size, y * tile_size, 0), glm::vec2(tile_size, tile_size), glm::vec4(r, g, b, 1)));
		}
	}

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
	addEnemy(50, 50, 32);

}

void Level::update(float timeElapsed)
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

	m_Player->update(timeElapsed);

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
			(*i)->update(timeElapsed);
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
			(*i)->update(timeElapsed);
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
			(*i)->update(timeElapsed);
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
	updateBackground();

	m_Label->position.x = m_Offset.x + 15;
	m_Label->position.y = m_Offset.y + m_Window.getHeight() - 45;
	m_Shader.setUniform2f("light_pos", glm::vec2(m_Player->getCenterX(), m_Player->getCenterY()));

	double x;
	double y;
	m_Window.getMousePos(x, y);
	m_Shader.setUniform2f("mouse_pos", glm::vec2(x, y));
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
	m_BGMoved = true;
	m_Offset.x += x;
	m_Offset.y += y;
	//std::cout << "offsetX : " << m_Offset.x << ", offsetY : " << m_Offset.y << "\n";

	m_Ortho = glm::translate(m_Ortho, glm::vec3(-x, -y, 0));
	m_Layer->setProjectionMatrix(m_Ortho);
}

void Level::updateBackground()
{
	if (!m_BGMoved) return;

	m_BGMoved = false;
	double r = 0;
	double g = 0;
	double b = 0;
	for (int x = 0; x < m_Window.getWidth() / m_TileSize; x++)
	{
		for (int y = 0; y < m_Window.getHeight() / m_TileSize; y++)
		{
			float val = m_Simplex.scaledOctaveNoise(5, 0.5, 1, 0, 1, (x + m_Offset.x) * 0.005f, (y + m_Offset.y) * 0.005f);
			if (val < 0.3)
			{
				r = 0;
				g = 0;
				b = 0.4;
			}
			else if (val < 0.4)
			{
				r = 0;
				g = 0;
				b = 0.8;
			}
			else if (val < 0.5)
			{
				r = 0.5;
				g = 0.5;
				b = 0;
			}
			else if (val < 0.8)
			{
				r = 0;
				g = 0.4;
				b = 0;
			}
			else
			{
				r = 0.9;
				g = 0.9;
				b = 0.9;
			}

			std::string tile_pos = std::to_string(x) + "_" + std::to_string(y);
			m_BackgroundTiles[tile_pos]->setPosition(x * m_TileSize + m_Offset.x, y * m_TileSize + m_Offset.y);
			m_BackgroundTiles[tile_pos]->setColor(r, g, b);
			//m_Layer->add(new Sprite(glm::vec3(x * tile_size, y * tile_size, 0), glm::vec2(tile_size, tile_size), glm::vec4(r, g, b, 1)));
		}
	}

}
