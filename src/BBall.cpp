#include "BBall.h"
#include "TextureManager.h"
#include "Util.h"

BBall::BBall()
{
	TextureManager::Instance()->load("../Assets/textures/EnemyCircle.png", "ball");
	TextureManager::Instance()->load("../Assets/textures/EnemySquare.png", "square");
	TextureManager::Instance()->load("../Assets/textures/EnemyTriangle.png", "triangle");

	auto size = TextureManager::Instance()->getTextureSize("ball");
	setWidth(size.x);
	setHeight(size.y);


	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

	getRigidBody()->isColliding = false;
	setType(BALLS);
}

BBall::~BBall()
= default;

void BBall::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	if (shape == 0) {
		TextureManager::Instance()->draw("ball", x, y, 0, 255, true);
	}
	else if (shape == 1) {
		TextureManager::Instance()->draw("square", x, y, 0, 255, true);
	}
	else if (shape == 2) {
		TextureManager::Instance()->draw("triangle", x, y, 0, 255, true);
	}

	
}

void BBall::update() {

	getRigidBody()->acceleration = glm::vec2(0, 98);
	float deltaTime = 1.0f / 60.0f;


	m_checkbounds();


	getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
}

void BBall::clean()
{
}

bool BBall::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float BBall::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void BBall::m_checkbounds()
{
	//left and right
	if (getTransform()->position.x >= 780)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x * -0.9f, getRigidBody()->velocity.y);
		getTransform()->position.x = 779;
	}

	if (getTransform()->position.x <= 20)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x * -0.9f, getRigidBody()->velocity.y);
		getTransform()->position.x = 21;
	}


	//up and down
	if (getTransform()->position.y >= 580)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x, getRigidBody()->velocity.y * -0.9f);
		getTransform()->position.y = 579;
	}

	if (getTransform()->position.y <= 20)
	{
		getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x, getRigidBody()->velocity.y * -0.9f);
		getTransform()->position.y = 21;

	}
}

void BBall::m_reset()
{
	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
}

