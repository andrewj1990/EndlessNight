#include "projectile.h"

Projectile::Projectile(int x, int y, const int& damage, Level& level, IncreaseDamageFunc idf)
	: Entity(x, y, level), m_ProjectileSpeed(1000.0f), m_Life(10000), m_ProjectileDamage(damage), damageFunc(idf)
{
	//m_ProjectileSpeed = 1;
	calcProjectileDir();
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(2.5f, 2.5f), glm::vec4(1, 1, 0, 1));
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(32.0f, 32.0f), TextureManager::get("PlayerSpriteSheet", 0, 0));
	m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(32, 32), glm::vec4(1, 1, 1, 1));
	//m_Sprite->setTexture(TextureManager::get("PlayerSpriteIdle"));
	m_Sprite->setTexture(TextureManager::get("Textures/Bullet.png", 0, 0));
	shadow = std::unique_ptr<Sprite>(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(64, 64), glm::vec4(1, 1, 1, 1)));
	shadow->setTexture(TextureManager::get("Textures/BulletGlow.png", 0, 0));
	//addToLevel(shadow.get());
	//m_Sprite = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(32, 32), glm::vec4(1, 1, 1, 1));
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

	// pathfinding test
	//int size = 16;

	//start = new Node((int)(m_X / size) * size, (int)(m_Y / size) * size);
	//goal = new Node((int)(mouseX / size) * size, (int)(mouseY / size) * size);
	//frontier.emplace(0, *start);

	//came_from[start->getInt()] = *start;
	//cost_so_far[start->getInt()] = 0;

	//Sprite* sprite = new Sprite(glm::vec3(goal->x, goal->y, 0), glm::vec2(2, 2), glm::vec4(0, 1, 1, 1));
	//m_Level.getLayer().add(sprite);

}

void Projectile::update(float timeElapsed)
{

	if (!collision())
	{
		m_Sprite->addDirection(m_Dx * timeElapsed, m_Dy * timeElapsed);
		shadow->addDirection(m_Dx * timeElapsed, m_Dy * timeElapsed);
		m_X += m_Dx * timeElapsed;
		m_Y += m_Dy * timeElapsed;
		//m_Sprite->setPosition(m_X, m_Y);
	}
	else {
		m_Destroy = true;
	}

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

	if (frontier.empty()) return;

	const std::unique_ptr<QuadTree>& qt = m_Level.getQuadTree();
	Node current = frontier.top().second;
	frontier.pop();

	Sprite* sprite = new Sprite(glm::vec3(current.x, current.y, 0), glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	m_Level.getLayer().add(sprite);
	if (current.getInt() == goal->getInt())
	{
		frontier = std::priority_queue<Element, std::vector<Element>, std::greater<Element>>();
		return;
	}
	// if already visited then continue
	for (Node next : current.neighbors())
	{
		int new_cost = cost_so_far[current.getInt()] + AStar::cost(next, qt);
		// if already visited then continue
		if (!came_from.count(next.getInt()) || new_cost < cost_so_far[next.getInt()])
		{
			cost_so_far[next.getInt()] = new_cost;
			int priority = new_cost + AStar::heuristic(next, *goal);
			frontier.emplace(priority, next);
			came_from[next.getInt()] = current;
		}

	}


}

bool Projectile::collision()
{
	//look at all the platforms in the level and check for any collisions
	//const std::unique_ptr<QuadTree>& q = m_Level.getQuadTree();
	//std::vector<Renderable*> platforms;
	//q->retrieve(platforms, m_Sprite);
	//for (Renderable* platform : platforms)
	//{
	//	const int& px = platform->getPosition().x;
	//	const int& py = platform->getPosition().y;
	//	const int& w = platform->getSize().x;
	//	const int& h = platform->getSize().y;

	//	if (m_X <= px + w && m_X >= px && m_Y >= py && m_Y <= py + h)
	//	{
	//		// if player is on a platform and moving
	//		// get the platforms colour and spawn particles the same colour as the platfroms
	//		glm::vec4 platformColour = platform->getColour();
	//		for (int i = 0; i < 5; ++i)
	//			m_Level.addParticle(new Particle(m_X, m_Y, m_Level, platformColour, 3.0f));

	//		m_Level.addEnemy(px, py, w / 2);
	//		return true;
	//	}
	//}

	const auto& enemies = m_Level.getEnemies();
	for (const auto& enemy : enemies)
	{
		const int& px = enemy->getSprite()->getPosition().x;
		const int& py = enemy->getSprite()->getPosition().y;
		const int& w = enemy->getSprite()->getSize().x;
		const int& h = enemy->getSprite()->getSize().y;

		//if (m_X <= px + w && m_X >= px && m_Y >= py && m_Y <= py + h)
		//{
		if (m_X < px + w && m_X > px && m_Y > py && m_Y < py + h ||
			m_X + m_Width < px + w && m_X + m_Width > px && m_Y > py && m_Y < py + h ||
			m_X < px + w && m_X > px && m_Y + m_Height > py && m_Y + m_Height < py + h ||
			m_X + m_Width < px + w && m_X + m_Width > px && m_Y + m_Height > py && m_Y + m_Height < py + h)
		{
			glm::vec4 platformColour(0, 1, 1, 1);
			for (int i = 0; i < 5; ++i)
				m_Level.addParticle(new Particle(m_X, m_Y, m_Level, platformColour, 3.0f));

			enemy->damage(m_ProjectileDamage);
			if (enemy->shouldDestroy())
			{
				m_Level.addEnemy(px, py, w * 0.85f);
				m_Level.addEnemy(px, py, w * 0.85f);
				if (damageFunc != nullptr) damageFunc(1.1f);
			}
			m_Level.addDamageText(std::to_string(m_ProjectileDamage), m_X, m_Y);
			return true;
		}
	}

	return false;
}

void Projectile::render()
{
}