#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"

class BBall final : public Sprite
{
public:
	BBall();
	~BBall();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	bool isColliding(GameObject*);
	float getDistance(GameObject*);


	void m_reset();
	int shape = 0;
private:
	glm::vec2 m_direction;
	void m_checkbounds();
	
};

#endif /* defined (__PLANE__) */