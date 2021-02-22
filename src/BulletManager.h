#pragma once

#include "Bullet.h"
#include "BulletPool.h"
#include "PlayScene.h"

class BulletManager
{
public:
	BulletManager(PlayScene*);
	void update();
private:
	BulletPool* m_pPool;
	PlayScene* m_pScene;

	void spawnBullet();

	float spawnTime;
	float timer;

};

