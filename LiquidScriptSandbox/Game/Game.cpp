#include "Game.h"
#include "../System/Global.h"
#include "../Utils/glfwKeyConversion.h"
#include <iostream>
#include "Addons/Addon.h"

Game::Game()
{
	global.gctx_ptr = &gctx;
}

Game::~Game()
{

}

void Game::ProcessEvents()
{
	
}

void Game::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	std::string skey = utils::KeyToString(key);
	global.keyCodes[skey] = true;

	if (action == GLFW_PRESS) {
		//std::cout << '"' << skey << '"' << " is pressed" << std::endl;
		global.gameInstance->localPlayer->onPress[skey] = true;
		global.gameInstance->localPlayer->isPressed[skey] = true;
	}else
	if (action == GLFW_RELEASE) {
		//std::cout << '"' << skey << '"' << " is released" << std::endl;
		global.gameInstance->localPlayer->isPressed[skey] = false;
	}
}

void Game::UpdateUI()
{
	ImGui::Begin("Addons");
	if (ImGui::Button("Reload")) {
		localPlayer->DestroyAddons();
		localPlayer->LoadAddons(localPlayer);
		localPlayer->InitAddons();
	}
	ImGui::Spacing();
	ImGui::Separator();
	for (int i = 0; i < (int)localPlayer->addons.size(); i++) {
		if(localPlayer->addons[i]->isActive) 
			ImGui::Text(localPlayer->addons[i]->name.c_str());
		else
			ImGui::TextColored(ImVec4(1, 1, 1, 0.2f), localPlayer->addons[i]->name.c_str());

		ImGui::SameLine(ImGui::GetWindowWidth() - 30);
		ImGui::Checkbox(("##"+localPlayer->addons[i]->name).c_str(), &localPlayer->addons[i]->isActive);
		ImGui::Separator();
	}
	ImGui::End();

	//ImGui::ShowDemoWindow();
}

void Game::Init()
{
	resources.Init();

	global.placeholderTexture = &resources.textures["placeholders/not_loaded_image"];

	localPlayer = gobj::Player_Ptr(new gobj::Player());
	players.push_back(localPlayer);
	localPlayer->LoadAddons(localPlayer);
	localPlayer->Init();
}

void Game::Update()
{
	gctx.camera.position.x += (localPlayer->position.x - gctx.camera.position.x) / 2.0F;
	gctx.camera.position.y += (localPlayer->position.y - gctx.camera.position.y) / 2.0F;


	std::map<std::string, bool>::iterator it = global.keyCodes.begin();
	while (it != global.keyCodes.end())
	{
		localPlayer->onPress[it->first] = false;
		it++;
	}

	for (int i = 0; i < (int)players.size(); i++)
	{
		players[i]->Update();
	}
}

void Game::Draw()
{
	gctx.StartDraw();

	for (int i = 0; i < (int)players.size(); i++)
	{
		players[i]->Draw();
	}
}
