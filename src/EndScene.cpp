#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	drawDisplayList();

	drawDisplayList();

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void EndScene::update()
{
	updateDisplayList();

}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}


}

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/Background.png", "background");

	const SDL_Color colour = { 255,0,0, 255 };

	m_pEndLabel = new Label("GAME OVER", "Consolas", 80, colour, glm::vec2(400.0f, 100.0f));
	m_pEndLabel->setParent(this);
	addChild(m_pEndLabel);

	m_pEndButton = new Button("../Assets/textures/restartButton.png", "restartButton");
	m_pEndButton->getTransform()->position = glm::vec2(400.0f, 500.0f);

	m_pEndButton->addEventListener(CLICK, [&]()-> void
	{
			m_pEndButton->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pEndButton->addEventListener(MOUSE_OVER, [&]()->void
	{
			m_pEndButton->setAlpha(128);
	});

	m_pEndButton->addEventListener(MOUSE_OUT, [&]()->void
	{
			m_pEndButton->setAlpha(255);
	});
	addChild(m_pEndButton);
}

void EndScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Previous Scene")) {
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}