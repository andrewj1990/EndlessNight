#include "level.h"

Level::Level(Window& window)
	: m_Window(window)
{
	m_Shader = new Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag");

	m_Offset = glm::vec2(0.0f, 0.0f);
	m_Ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	m_Layer = new Layer(m_Shader, m_Ortho);

	//for (float i = 0; i < 3280; i += 60.0f)
	//{
	//	for (float j = 0; j < 720; j += 60.0f)
	//	{
	//		m_Layer->add(new Renderable(glm::vec3(i, j, 0), glm::vec2(50.0f, 50.0f), glm::vec4(0, 0, rand() % 1000 / 1000.0f, 1)));
	//	}
	//}

	Platform* platform = new Platform(*m_Layer, m_Window.getWidth() / 3, 0, m_Window.getWidth() / 2, m_Window.getHeight() / 2);
	m_Platforms.push_back(platform);
	m_Player = new Player(m_Window.getWidth() / 2, m_Window.getHeight() / 2, *m_Layer, *this, m_Window);
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

float i = 0;
void Level::update()
{
	
	double x;
	double y;
	m_Window.getMousePos(&x, &y);
	x += m_Offset.x;
	y += m_Offset.y;
	//std::cout << "x : " << x << ", y : " << y << "\n";
	if (glfwGetMouseButton(m_Window.getWindow(), GLFW_MOUSE_BUTTON_1))
	{
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}

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

}

void Level::render()
{
	double x, y;
	m_Window.getMousePos(&x, &y);
	m_Shader->setUniform2f("light_pos", glm::vec2(x * 16 / 1280, 9 - (y * 9 / 720)));
	m_Layer->render();
}

void Level::addParticle(Particle* particle)
{
	m_Particles.push_back(particle);
}

void Level::addPlatform(Platform* platform)
{
	m_Platforms.push_back(platform);
}

void Level::moveCamera(const float& x, const float& y)
{
	m_Offset.x += x;
	m_Offset.y += y;
//	std::cout << "offsetX : " << m_Offset.x << ", offsetY : " << m_Offset.y << "\n";

	m_Ortho = glm::translate(m_Ortho, glm::vec3(-x, -y, 0));
	m_Layer->setProjectionMatrix(m_Ortho);
}