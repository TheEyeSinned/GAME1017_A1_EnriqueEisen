#include "Brick.h"
#include "TextureManager.h"
#include "Util.h"
#include <iostream>

using namespace std;

Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/Brick.png", "brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);


	getTransform()->position = glm::vec2(400.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BRICK);

}

Brick::~Brick()
= default;

void Brick::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("brick", x, y, 0, 255, true);
}

void Brick::update()
{
	//getTransform()->position = getRigidBody()->velocity;


	newPosition = getTransform()->position;
	
	getRigidBody()->velocity.x = oldPosition.x - newPosition.x  ;

	oldPosition = getTransform()->position;

	std::cout << "old Position" << oldPosition.x << std::endl;
	std::cout << "new Position" << newPosition.x << std::endl;
	std::cout << "difference" << getRigidBody()->velocity.x << std::endl;

	m_checkbounds();
}

void Brick::clean()
{
}


bool Brick::isColliding(GameObject* pOther)
{
	float myRadius = getWidth() * 0.5f;
	float otherRadius = pOther->getWidth() * 0.5f;

	return (getDistance(pOther) <= myRadius + otherRadius);
}

float Brick::getDistance(GameObject* pOther)
{
	glm::vec2 myPos = getTransform()->position;
	glm::vec2 otherPos = pOther->getTransform()->position;

	// Use pythagorean to calculate distance c = sqrt(a^2 + b^2)
	float a = myPos.x - otherPos.x;
	float b = myPos.y - otherPos.y;
	return sqrt(a * a + b * b);
}

void Brick::m_checkbounds()
{
	if (getTransform()->position.x > 790)
	{
		getTransform()->position = glm::vec2(790.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 10)
	{
		getTransform()->position = glm::vec2(10.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > 590)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 590.0f);
	}

	if (getTransform()->position.y < 10)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 10.0f);
	}
}
