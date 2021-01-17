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
	InitAddons();
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

void gobj::Player::InitAddons()
{
	for (int i = 0; i < (int)addons.size(); i++)
	{
		addons[i]->Init();
	}
}

void gobj::Player::DestroyAddons()
{
	for (int i = 0; i < (int)addons.size(); i++)
	{
		addons[i]->Destroy();
	}
	addons.clear();
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

bool gobj::Player::GetBool(std::string key)
{
	return var_bool[key];
}

float gobj::Player::GetNum(std::string key)
{
	return var_num[key];
}

std::string gobj::Player::GetStr(std::string key)
{
	return var_str[key];
}

void gobj::Player::SetBool(std::string key, bool value)
{
	var_bool[key] = value;
}

void gobj::Player::SetNum(std::string key, float value)
{
	var_num[key] = value;
}

void gobj::Player::SetStr(std::string key, std::string value)
{
	var_str[key] = value;
}
