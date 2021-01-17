#include "Game.h"
#include "../System/Global.h"
#include "../Utils/glfwKeyConversion.h"

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
}

void Game::Init()
{
	resources.Init();

	localPlayer = gobj::Player_Ptr(new gobj::Player());
	players.push_back(localPlayer);
	localPlayer->LoadAddons(localPlayer);
	localPlayer->Init();
}

void Game::Update()
{
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
