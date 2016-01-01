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

	m_Player = new Player(5, 5, *m_Layer);
}

void Level::update()
{
	double x, y;
	m_Window.getMousePos(&x, &y);

	//std::cout << "x : " << x << ", y : " << y << "\n";

	//m_Player->update(x, y);
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_UP))
	{
		glm::mat4 ortho = glm::ortho(0.0f, ++ox, 0.0f, ++oy, -1.0f, 1.0f);
		m_Layer->setProjectionMatrix(ortho);
	}

	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_DOWN))
	{
		glm::mat4 ortho = glm::ortho(0.0f, --ox, 0.0f, --oy, -1.0f, 1.0f);
		m_Layer->setProjectionMatrix(ortho);
	}


	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_SPACE))
	{
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}

	for (Particle* particle : m_Particles)
	{
		particle->update();
	}

	double speed = 5;
	x = m_Player->getX();
	y = m_Player->getY();
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_W)) {
		m_Player->update(0, speed);
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_S)) {
		m_Player->update(0, -speed);
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_A)) {
		m_Player->update(-speed, 0);
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_D)) {
		m_Player->update(speed, 0);
		m_Particles.push_back(new Particle(x, y, *m_Layer));
	}

}

void Level::render()
{
	double x, y;
	m_Window.getMousePos(&x, &y);
	m_Shader->setUniform2f("light_pos", glm::vec2(x * 16 / 1280, 9 - (y * 9 / 720)));
	m_Layer->render();
}