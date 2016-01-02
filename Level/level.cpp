#include "level.h"

Level::Level(Window& window)
	: m_Window(window)
{
	m_Shader = new Shader("Shaders/vertShader.vert", "Shaders/fragShader.frag");

	ox = m_Window.getWidth();
	oy = m_Window.getHeight();
	glm::mat4 ortho = glm::ortho(0.0f, ox, 0.0f, oy, -1.0f, 1.0f);
	m_Layer = new Layer(m_Shader, ortho);

	for (float i = 0; i < 1280; i += 6.0f)
	{
		for (float j = 0; j < 720; j += 6.0f)
		{
			m_Layer->add(new Renderable(glm::vec3(i, j, 0), glm::vec2(5.0f, 5.0f), glm::vec4(0, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	Platform* platform = new Platform(*m_Layer, m_Window.getWidth() / 3, 0, m_Window.getWidth() / 2, m_Window.getHeight() / 2);
	m_Platforms.push_back(platform);
	m_Player = new Player(m_Window.getWidth() / 2, m_Window.getHeight() / 2, *m_Layer, *this, m_Window);
}

void Level::update()
{
	m_Player->update();

	// check if any particles need to be deleted
	for (auto i = m_Particles.begin(); i != m_Particles.end(); )
	{
		if ((*i)->shouldDestroy())
		{
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