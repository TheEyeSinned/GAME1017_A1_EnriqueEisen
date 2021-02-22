#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


PlayScene::PlayScene()
{
	PlayScene::start();

	
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	
	drawDisplayList();

	if (isRunning == false) {
		TextureManager::Instance()->draw("pause", 400, 300, 0, 255, true);
	}

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	if (isRunning == true) 
	{
		updateDisplayList();


		if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimerDuration) {
			SpawnBullet();
		}

		std::vector<Bullet*>& activeBullets = m_pPool->all;
		for (std::vector<Bullet*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); myiter++) {
			Bullet* bullet = *myiter;
			if (bullet->active && bullet->getTransform()->position.y >= 610) {
				m_pPool->Despawn(bullet);
				break;
			}
			if (bullet->active && m_pPlayer->isColliding(bullet)) {

				m_pPool->Despawn(bullet);
				SoundManager::Instance().playSound("boom", 0, -1);
				TheGame::Instance()->changeSceneState(END_SCENE);
			}
		}
		
		m_pResumeButton->getTransform()->position = glm::vec2(1000.0f, 1000.0f);
	}
	else if (isRunning == false)
	{
		
		
		m_pResumeButton->getTransform()->position = glm::vec2(400.0f, 500.0f);

	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
		EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlayer->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlayer->moveRight();
	}
	else {
		m_pPlayer->stopMovingX();
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)) {
		m_pPlayer->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) {
		m_pPlayer->moveDown();
	}
	else {
		m_pPlayer->stopMovingY();
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_P) && isRunning == true) {
		isRunning = false;
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_O) && isRunning == false) {
		isRunning = true;
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");

	TextureManager::Instance()->load("../Assets/textures/Pause.png", "pause");

	SoundManager::Instance().load("../Assets/audio/boom.mp3", "boom", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(30);


	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	
	m_pResumeButton = new Button();
	m_pResumeButton->addEventListener(CLICK, [&]()-> void
		{
			m_pResumeButton->setActive(false);
			isRunning = true;
		});

	m_pResumeButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pResumeButton->setAlpha(128);
		});

	m_pResumeButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pResumeButton->setAlpha(255);
		});
	addChild(m_pResumeButton);
	

	m_pPool = new BulletPool(numBullets);
	for (std::vector<Bullet*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++) {
		Bullet* bullet = *myiter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::SpawnBullet() {
	Bullet* bullet = m_pPool->Spawn();
	if (bullet) {
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0 /*rand() % 100 * -1*/);
	}

	bulletSpawnTimerStart = SDL_GetTicks();
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Start Scene")) {
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (ImGui::Button("Next Scene")) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}