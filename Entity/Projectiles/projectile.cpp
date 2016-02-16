#include "projectile.h"

Projectile::Projectile(int x, int y, Level& level)
	: Entity(x, y, level), m_ProjectileSpeed(15.0f), m_Life(10000)
{
	//m_ProjectileSpeed = 1;
	calcProjectileDir();
	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(2.5f, 2.5f), glm::vec4(1, 1, 0, 1));
	addToLevel(m_Sprite);
}

void Projectile::calcProjectileDir()
{
	double mouseX;
	double mouseY;
	m_Level.getWindowClass().getMousePos(mouseX, mouseY);
	mouseX += m_Level.getOffset().x;
	mouseY += m_Level.getOffset().y;

	// get projectile direction
	float angle = std::atan2f(mouseX - m_X, mouseY - m_Y);
	m_Dx = std::sinf(angle) * m_ProjectileSpeed;
	m_Dy = std::cosf(angle) * m_ProjectileSpeed;

	std::unordered_map<int, Node> mp;
	//std::cout << "m_X : " << m_X << " , m_Y : " << m_Y << " | mouseX : " << mouseX << " , mouseY : " << mouseY << "\n";

	int size = 16;
	const std::unique_ptr<QuadTree>& qt = m_Level.getQuadTree();
	mp = aStarSearch((int)(m_X / size) * size, (int)(m_Y / size) * size, glm::vec2((int)(mouseX / size) * size, (int)(mouseY / size) * size), qt);

	Node current((int)(mouseX / size) * size, (int)(mouseY / size) * size);
	Node start((int)(m_X / size) * size, (int)(m_Y / size) * size);
	path.push_back(current);
	while (current.getInt() != start.getInt())
	{
		current = mp[current.getInt()];
		path.push_back(current);
	}
}

void Projectile::update()
{
	if (path.size() <= 0) return;
	Node current = path.back();
	path.pop_back();
	m_X = current.x;
	m_Y = current.y;

	if (!collision())
	{
		//m_Sprite->addDirection(m_Dx, m_Dy);
		m_Sprite->setPosition(m_X, m_Y);
	}
	else {
		m_Destroy = true;
	}

	//m_Sprite->fade();

	float alpha = m_Sprite->getColour().w;
	// set to destroy particle if life runs out
	if (alpha <= 0.05f)
	{
		m_Destroy = true;
	}

	if (--m_Life < 0)
	{
		m_Destroy = true;
	}
}

bool Projectile::collision()
{
	//look at all the platforms in the level and check for any collisions
	const std::unique_ptr<QuadTree>& q = m_Level.getQuadTree();
	std::vector<Renderable*> platforms;
	q->retrieve(platforms, m_Sprite);
	for (Renderable* platform : platforms)
	{
		platform->setColor(0, 1, 0);
		const int& px = platform->getPosition().x;
		const int& py = platform->getPosition().y;
		const int& w = platform->getSize().x;
		const int& h = platform->getSize().y;

		if (m_X <= px + w && m_X >= px && m_Y >= py && m_Y <= py + h)
		{
			// if player is on a platform and moving
			// get the platforms colour and spawn particles the same colour as the platfroms
			glm::vec4 platformColour = platform->getColour();
			for (int i = 0; i < 5; ++i)
				m_Level.addParticle(new Particle(m_X, m_Y, m_Level, platformColour, 3.0f));
			return true;
		}
	}

	return false;
}

void Projectile::render()
{
}