#include "player.h"

Player::Player(const int& x, const int& y, Layer& layer, Level& level, Window& window)
	: m_X(x), m_Y(y), m_Layer(layer), m_Level(level), m_Window(window)
{
	m_PlayerSpeed = 3.0;
	init();
}

void Player::init()
{
	const float& scale = 2.0f;
	const float& body_height = 5.0f * scale;
	const float& body_width = 4.0f * scale;
	const float& leg_height = 2.0f * scale;
	const float& leg_width = 1.0f * scale;
	const float& arm_height = 3.0f * scale;
	const float& arm_width = 1.0f * scale;
	const float& head_size = 2.0f * scale;

	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(body_width, body_height), glm::vec4(1, 0, 1, 0.5)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X - arm_width, m_Y + body_height - arm_height, 0), glm::vec2(arm_width, arm_height), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width, m_Y + body_height - arm_height, 0), glm::vec2(arm_width, arm_height), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width / 4.0f, m_Y + body_height, 0), glm::vec2(head_size, head_size), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 0.5f, m_Y - leg_height, 0), glm::vec2(leg_width, leg_height), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width - leg_width - 0.5f, m_Y - leg_height, 0), glm::vec2(leg_width, leg_height), glm::vec4(1, 1, 0, 1)));

	for (Sprite* sprite : m_PlayerBody)
	{
		m_Layer.add(sprite);
	}
}

void Player::update()
{
	double dx = 0;
	double dy = 0;

	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_W)) {
		dy += m_PlayerSpeed + 10;
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_S)) {
		dy -= m_PlayerSpeed;
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_A)) {
		dx -= m_PlayerSpeed;
	}
	if (glfwGetKey(m_Window.getWindow(), GLFW_KEY_D)) {
		dx += m_PlayerSpeed;
	}

	// gravity
	if (!collision(m_X, m_Y - m_PlayerSpeed))
	{
		move(0, -m_PlayerSpeed);
	}

	// check if the next tile is not collidable and move
	if (!collision(m_X, m_Y + dy))
	{
		move(0, dy);
	}

	if (!collision(m_X + dx, m_Y))
	{
		move(dx, 0);
	}


}

void Player::render()
{

	
}

void Player::move(const double& dx, const double& dy)
{
	if (dx == 0 && dy == 0) return;

	m_Level.addParticle(new Particle(m_X, m_Y, m_Layer));
	m_Level.addParticle(new Particle(m_X, m_Y, m_Layer));
	for (Sprite* sprite : m_PlayerBody)
	{
		sprite->addDirection(dx, dy);
	}

	m_X += dx;
	m_Y += dy;
}

bool Player::collision(int x, int y)
{
	// look at all the platforms in the level and check for any collisions
	std::vector<Platform*>& platforms = m_Level.getPlatforms();
	for (Platform* platform : platforms)
	{
		const int& px = platform->getX();
		const int& py = platform->getY();
		const int& w = platform->getWidth();
		const int& h = platform->getHeight();

		//std::cout << "x : " << x << ", y : " << y << " | px : " << px << ", py : " << py
		//	<< ", px2 : " << (px + w) << ", py2 : " << (py + h) << "\n";
		
		if (x < px + w && x > px && y > py && y < py + h) return true;
		
	}

	return false;
}