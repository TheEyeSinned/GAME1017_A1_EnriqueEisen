#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet() {
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");

	auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);

	setType(ENEMY);

	

	Reset();
}

Bullet::~Bullet()
= default;

void Bullet::draw() {
	if (active) {
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
	}
}

void Bullet::update() {
	if (active) {
		float deltaTime = 1.0f / 60.0f;
		getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
	}

}

void Bullet::clean() {

}

void Bullet::Reset()
{
	getRigidBody()->velocity = glm::vec2(0.0f, 100.0f);
	getRigidBody()->acceleration = glm::vec2(0, 9.8);
	getRigidBody()->isColliding = false;
}
