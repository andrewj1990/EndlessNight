#include "player.h"

Player::Player(const int& x, const int& y, Level& level)
	: Entity(x, y, level)
{
	m_Width = 10;
	m_Height = 10;
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

	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(10, 10), glm::vec4(0.4f, 0.3f, 0.7f, 1)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(body_width, body_height), glm::vec4(1, 0, 1, 0.5)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X - arm_width, m_Y + body_height - arm_height, 0), glm::vec2(arm_width, arm_height), glm::vec4(1, 0, 0, 1)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width, m_Y + body_height - arm_height, 0), glm::vec2(arm_width, arm_height), glm::vec4(1, 0, 0, 1)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width / 4.0f, m_Y + body_height, 0), glm::vec2(head_size, head_size), glm::vec4(1, 0, 0, 1)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 0.5f, m_Y - leg_height, 0), glm::vec2(leg_width, leg_height), glm::vec4(1, 0, 0, 1)));
	//m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + body_width - leg_width - 0.5f, m_Y - leg_height, 0), glm::vec2(leg_width, leg_height), glm::vec4(1, 1, 0, 1)));

	// add all the body pieces to the level
	for (Sprite* sprite : m_PlayerBody)
	{
		addToLevel(sprite);
	}
}

void Player::update()
{
	double dx = 0;
	double dy = -m_PlayerSpeed;

	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_SPACE)) {
		dy += m_PlayerSpeed + 10;
		m_Level.addParticle(new Particle(getCenterX(), getCenterY(), m_Level));
		m_Level.addParticle(new Particle(getCenterX(), getCenterY(), m_Level));
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_S)) {
		dy -= m_PlayerSpeed;
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_A)) {
		dx -= m_PlayerSpeed;
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_D)) {
		dx += m_PlayerSpeed;
	}

	if (glfwGetMouseButton(m_Level.getWindow(), GLFW_MOUSE_BUTTON_1))
	{
		m_Level.addProjectile(new Projectile(getCenterX(), getCenterY(), m_Level));
	}

	// gravity
	if (!collision(m_X, m_Y - 1, true, dx, 0))
	{
		move(0, -1);
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

	for (Sprite* sprite : m_PlayerBody)
	{
		sprite->addDirection(dx, dy);
	}

	m_Level.moveCamera(dx, dy);

	m_X += dx;
	m_Y += dy;
}

bool Player::collision(int x, int y, bool spawn_particles, int dx, int dy)
{
	// look at all the platforms in the level and check for any collisions
	std::vector<Entity*>& platforms = m_Level.getPlatforms();
	for (Entity* platform : platforms)
	{
		const int& px = platform->getX();
		const int& py = platform->getY();
		const int& w = platform->getWidth();
		const int& h = platform->getHeight();

		if (x < px + w && x > px && y > py && y < py + h ||
			x + m_Width < px + w && x + m_Width > px && y > py && y < py + h ||
			x < px + w && x > px && y + m_Height > py && y + m_Height < py + h ||
			x + m_Width < px + w && x + m_Width > px && y + m_Height > py && y + m_Height < py + h)
		{
			// if player is on a platform and moving
			// get the platforms colour and spawn particles the same colour as the platfroms
			if (spawn_particles && (dx != 0 || dy != 0))
			{
				glm::vec4 colour = platform->getSprite()->getColour();
				m_Level.addParticle(new Particle(getCenterX(), m_Y, m_Level, colour));
			}
			return true;
		}
	}

	return false;
}