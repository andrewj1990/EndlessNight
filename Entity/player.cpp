#include "player.h"

Player::Player(const int& x, const int& y, Layer& layer)
	: m_X(x), m_Y(y), m_Layer(layer)
{
	//m_Renderable = new Renderable(glm::vec3(m_X, m_Y, 0), glm::vec2(0.4f,0.6f), glm::vec4(1, 0, 1, 0.5));
	//m_Layer.add(m_Renderable);
//	player_body = new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(0.4f, 0.4f), glm::vec4(1, 1, 1, 0.5));
//	m_Layer.add(player_body);
//	m_Layer.add(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(0.4f, 0.4f), glm::vec4(1, 1, 1, 0.5)));
	//m_Layer.add(new Sprite(glm::vec3(m_X - 0.1f, m_Y + 0.1f, 0), glm::vec2(0.1f, 0.3f), glm::vec4(1, 0, 0, 1)));
	//m_Layer.add(new Sprite(glm::vec3(m_X + 0.4f, m_Y + 0.1f, 0), glm::vec2(0.1f, 0.3f), glm::vec4(1, 0, 0, 1)));
	//m_Layer.add(new Sprite(glm::vec3(m_X + 0.1f, m_Y + 0.4f, 0), glm::vec2(0.2f, 0.2f), glm::vec4(1, 0, 0, 1)));
	//m_Layer.add(new Sprite(glm::vec3(m_X + 0.05f, m_Y - 0.2f, 0), glm::vec2(0.1f, 0.2f), glm::vec4(1, 0, 0, 1)));
	//m_Layer.add(new Sprite(glm::vec3(m_X + 0.2f, m_Y - 0.2f, 0), glm::vec2(0.1f, 0.2f), glm::vec4(1, 1, 0, 1)));

	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X, m_Y, 0), glm::vec2(4.0f, 4.0f), glm::vec4(1, 0, 1, 0.5)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X - 1.0f, m_Y + 1.0f, 0), glm::vec2(1.0f, 3.0f), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 4.0f, m_Y + 1.0f, 0), glm::vec2(1.0f, 3.0f), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 1.0f, m_Y + 4.0f, 0), glm::vec2(2.0f, 2.0f), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 0.5f, m_Y - 2.0f, 0), glm::vec2(1.0f, 2.0f), glm::vec4(1, 0, 0, 1)));
	m_PlayerBody.push_back(new Sprite(glm::vec3(m_X + 2.0f, m_Y - 2.0f, 0), glm::vec2(1.0f, 2.0f), glm::vec4(1, 1, 0, 1)));

	for (Sprite* sprite : m_PlayerBody)
	{
		m_Layer.add(sprite);
	}

}

void Player::update(const double& dx, const double& dy)
{
	for (Sprite* sprite : m_PlayerBody)
	{
		glm::vec3 position = sprite->getPosition();
//		sprite->setPosition(position.x + dx, position.y + dy);
		sprite->addDirection(dx, dy);

	}
	m_X += dx;
	m_Y += dy;
}

void Player::render()
{

	
}