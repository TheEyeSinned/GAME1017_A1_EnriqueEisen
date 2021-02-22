#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Player.h"
#include "Button.h"
#include "Bullet.h"
#include "BulletPool.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	int numBullets = 10;
private:
	// IMGUI function
	void GUI_Function() const;
	std::string m_guiTitle;

	bool isRunning = true;

	Button* m_pResumeButton;

	const float bulletSpawnTimerDuration = 500.0f;
	float bulletSpawnTimerStart;
	
	glm::vec2 m_mousePosition;

	BulletPool* m_pPool;

	Player* m_pPlayer;

	Button* m_pBackButton;
	Button* m_pNextButton;


	void SpawnBullet();
};

#endif /* defined (__PLAY_SCENE__) */