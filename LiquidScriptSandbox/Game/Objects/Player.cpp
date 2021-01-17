#include "Player.h"
#include "../Addons/Addon.h"
#include "../../Utils/FileManager.h"

gobj::Player::Player()
{

}

gobj::Player::~Player()
{

}

void gobj::Player::Init()
{
	for (int i = 0; i < (int)addons.size(); i++)
	{
		addons[i]->Init();
	}
}

void gobj::Player::Update()
{
	for (int i = 0; i < (int)addons.size(); i++)
	{
		addons[i]->Update();
	}
}

void gobj::Player::Draw()
{
	for (int i = 0; i < (int)addons.size(); i++)
	{
		addons[i]->Draw();
	}
}

void gobj::Player::LoadAddons(Player_Ptr self)
{
	utils::DirectoryList folders = utils::GetDirectories("../Addons");
	for (int i = 0; i < (int)folders.size(); i++) {
		addons.push_back(std::shared_ptr<Addon>(new Addon(folders[i], self)));
	}
}

bool gobj::Player::IsPressed(std::string key)
{
	return isPressed[key];
}

bool gobj::Player::OnPress(std::string key)
{
	return onPress[key];
}
