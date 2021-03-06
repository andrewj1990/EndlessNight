#include "player.h"

Player::Player(const int& x, const int& y, Level& level)
	: Entity(x, y, level), m_PlayerSpriteSheet("Textures/PlayerSpritesheet9.png"), m_Anim(0),
	m_PlayerDamage(10)
{
	first = true;
	m_ProjectileDelay = 0;
	m_Width = 10;
	m_Height = 10;
	m_PlayerSpeed = 1.0;

	//m_PlayerSpriteSheet = std::unique_ptr<SpriteSheet>(new SpriteSheet("Textures/PlayerSpritesheet4.png"));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 0, 0, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 0, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 1, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 2, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 3, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 4, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 5, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 6, 1, 32, 32));
	TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 7, 1, 32, 32));
	//TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 0, 1, 64, 64));
	//TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 1, 1, 64, 64));
	//TextureManager::add(new Texture(m_PlayerSpriteSheet, "PlayerSpriteSheet", 2, 1, 64, 64));

		
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(10, 10), glm::vec4(0.4f, 0.3f, 0.7f, 1));
	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(32, 32), glm::vec4(1, 1, 1, 1));
	//m_Sprite->setTexture(TextureManager::get("PlayerSpriteIdle"));
	m_Sprite->setTexture(TextureManager::get("Textures/PlayerSpritesheet10.png", 0, 0));
	m_Level.getLayer().add(m_Sprite);
}

void Player::update(float timeElapsed)
{
	double dx = 0;
	//double dy = -m_PlayerSpeed;
	double dy = 0;

	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_LEFT_SHIFT))
	{
		m_PlayerSpeed = 2.0;
	}
	else
	{
		m_PlayerSpeed = 1.0;
	}

	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_W)) {
	//if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_SPACE)) {
		dy += m_PlayerSpeed;
		//m_Level.addParticle(new Particle(getCenterX(), getCenterY(), m_Level));
		//m_Level.addParticle(new Particle(getCenterX(), getCenterY(), m_Level));
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_S)) {
		dy -= m_PlayerSpeed;
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_A)) {
		dx -= m_PlayerSpeed;
		//m_Sprite->setTexture(TextureManager::get("PlayerSpriteSheet", 0, 0));
	}
	if (glfwGetKey(m_Level.getWindow(), GLFW_KEY_D)) {
		//m_Sprite->setTexture(TextureManager::get("PlayerSpriteSheet", m_Anim % 8, 1));
		dx += m_PlayerSpeed;
	}

	m_Anim++;

	m_ProjectileDelay++;
	if (m_ProjectileDelay > 10 && glfwGetMouseButton(m_Level.getWindow(), GLFW_MOUSE_BUTTON_1))
	//if (m_Level.getWindowClass().isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) && first)
	{
		m_ProjectileDelay = 0;
		first = false;
		m_Level.addProjectile(new Projectile(getCenterX(), getCenterY(), m_PlayerDamage, m_Level, std::bind(&Player::increaseDamage, this, std::placeholders::_1)));
	}

	// gravity
	//if (!collision(m_X, m_Y - 1, true, dx, 0))
	//{
	//	fall(-1);
	//}

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

	m_Level.moveCamera(dx, dy);
	m_Sprite->addDirection(dx, dy);

	m_X += dx;
	m_Y += dy;
}

void Player::fall(const double& dy)
{
	move(0, dy);
	//m_Level.addBlock(m_X, m_Y - 100);
}

void Player::increaseDamage(float multiplier)
{
	m_PlayerDamage *= multiplier;
}

bool Player::collision(int x, int y, bool spawn_particles, int dx, int dy)
{
	// look at all the platforms in the level and check for any collisions
	const std::unique_ptr<QuadTree>& q = m_Level.getQuadTree();
	std::vector<Renderable*> platforms;
	//q->retrieve(platforms, x, y, m_Width, m_Height);
	q->retrieve(platforms, x, y, 0, 0);
	q->retrieve(platforms, x + m_Width, y, 0, 0);
	q->retrieve(platforms, x, y + m_Height, 0, 0);
	q->retrieve(platforms, x + m_Width, y + m_Height, 0, 0);

	const std::vector<Renderable*> platforms2 = m_Level.getPlatform();
	for (Renderable* platform : platforms)
	{
		//const int& px = platform->getX();
		//const int& py = platform->getY();
		//const int& w = platform->getWidth();
		//const int& h = platform->getHeight();
		const int& px = platform->getPosition().x;
		const int& py = platform->getPosition().y;
		const int& w = platform->getSize().x;
		const int& h = platform->getSize().y;

		if (x < px + w && x > px && y > py && y < py + h ||
			x + m_Width < px + w && x + m_Width > px && y > py && y < py + h ||
			x < px + w && x > px && y + m_Height > py && y + m_Height < py + h ||
			x + m_Width < px + w && x + m_Width > px && y + m_Height > py && y + m_Height < py + h)
		{
			// if player is on a platform and moving
			// get the platforms colour and spawn particles the same colour as the platfroms
			if (spawn_particles && (dx != 0 || dy != 0))
			{
				glm::vec4 colour = platform->getColour();
				m_Level.addParticle(new Particle(getCenterX(), m_Y, m_Level, colour));
			}
			return true;
		}
	}

	const auto& enemies = m_Level.getEnemies();
	for (const auto& enemy : enemies)
	{
		const int& px = enemy->getX();
		const int& py = enemy->getY();
		const int& w = enemy->getSize();
		const int& h = enemy->getSize();

		if (x < px + w && x > px && y > py && y < py + h ||
			x + m_Width < px + w && x + m_Width > px && y > py && y < py + h ||
			x < px + w && x > px && y + m_Height > py && y + m_Height < py + h ||
			x + m_Width < px + w && x + m_Width > px && y + m_Height > py && y + m_Height < py + h)
		{
			// if player is on a platform and moving
			// get the platforms colour and spawn particles the same colour as the platfroms
			if (spawn_particles && (dx != 0 || dy != 0))
			{
				glm::vec4 colour(1, 1, 0, 1);
				m_Level.addParticle(new Particle(getCenterX(), m_Y, m_Level, colour));
			}
			return true;
		}
	}


	return false;
}
