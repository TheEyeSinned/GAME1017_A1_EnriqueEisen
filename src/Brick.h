#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"

class Brick final : public Sprite
{
public:
	Brick();
	~Brick();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	bool isColliding(GameObject*);
	float getDistance(GameObject*);

	glm::vec2 oldPosition = glm::vec2(0.0f, 0.0f);
	glm::vec2 newPosition;
private:
	glm::vec2 m_direction;
	void m_checkbounds();


};

#endif /* defined (__PLANE__) */
