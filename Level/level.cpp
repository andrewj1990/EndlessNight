#include "level.h"
#include "../Graphics/label.h"

Label* label = new Label("fps", 0, 0, glm::vec4(1,0,1,0.5));
Level::Level(Window& window)
	: m_Window(window)
{
	m_Shader = new Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag");

	m_Offset = glm::vec2(0.0f, 0.0f);
	m_Ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	m_Layer = new Layer(m_Shader, m_Ortho);

	GLint texID[] = 
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	m_Shader->setUniform1iv("textures", 10, texID);

	Texture* tex = new Texture("test.png");
	Texture* tex2 = new Texture("test2.png");

	//Sprite* sprite = new Sprite(glm::vec3(0, 0, 0), glm::vec2(100, 100), tex);
	//m_Layer->add(sprite);
	//Sprite* sprite2 = new Sprite(glm::vec3(100, 100, 0), glm::vec2(100, 100), tex2);
	//m_Layer->add(sprite2);

	for (float i = 0; i < 3280; i += 60.0f)
	{
		for (float j = 0; j < 720; j += 60.0f)
		{
			m_Layer->add(new Sprite(glm::vec3(i, j, 0), glm::vec2(50.0f, 50.0f), rand() % 2 == 0 ? tex : tex2));
			//m_Layer->add(new Renderable(glm::vec3(i, j, 0), glm::vec2(50.0f, 50.0f), glm::vec4(0, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	m_Layer->add(label);

	Platform* platform = new Platform(m_Window.getWidth() / 3, 0, m_Window.getWidth() / 2, m_Window.getHeight() / 2, *this);
	m_Platforms.push_back(platform);
	m_Player = new Player(m_Window.getWidth() / 2, m_Window.getHeight() / 2, *this);


	int center = 0;
	int center_width = 1280;
	int center_height = 720;

	Zone* zone1 = new Zone(1280, 720, m_Window, *m_Layer, *this);
	Zone* zone2 = new Zone(1280, 0, m_Window, *m_Layer, *this);
	Zone* zone3 = new Zone(1280, -720, m_Window, *m_Layer, *this);
	Zone* zone4 = new Zone(0, 720, m_Window, *m_Layer, *this);
	Zone* zone5 = new Zone(0, 0, m_Window, *m_Layer, *this);
	Zone* zone6 = new Zone(0, -720, m_Window, *m_Layer, *this);
	Zone* zone7 = new Zone(-1280, 720, m_Window, *m_Layer, *this);
	Zone* zone8 = new Zone(-1280, 0, m_Window, *m_Layer, *this);
	Zone* zone9 = new Zone(-1280, -720, m_Window, *m_Layer, *this);
}

void Level::update()
{
	double x;
	double y;
	m_Window.getMousePos(x, y);
	x += m_Offset.x;
	y += m_Offset.y;
	//std::cout << "x : " << x << ", y : " << y << "\n";


	//if (glfwGetMouseButton(m_Window.getWindow(), GLFW_MOUSE_BUTTON_1))
	//{
	//	m_Particles.push_back(new Particle(x, y, *this));
	//}

	m_Player->update();
//	std::cout << "particles : " << m_Particles.size() << "\n";

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


	label->text = std::to_string(x) + ", " + std::to_string(y);


//	std::cout << "number of platforms : " << m_Platforms.size() << "\n";
//	std::cout << "number of projectiles : " << m_Projectiles.size() << "\n";
}

void Level::render()
{
	m_Shader->setUniform2f("light_pos", glm::vec2(m_Player->getCenterX(), m_Player->getCenterY()));
	m_Layer->render();
}

void Level::addParticle(Entity* particle)
{
	m_Particles.push_back(particle);
//	m_Layer->add(particle->getSprite());
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
	std::cout << "offsetX : " << m_Offset.x << ", offsetY : " << m_Offset.y << "\n";

	m_Ortho = glm::translate(m_Ortho, glm::vec3(-x, -y, 0));
	m_Layer->setProjectionMatrix(m_Ortho);
}