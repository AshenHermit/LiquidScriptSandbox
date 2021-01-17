#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "../Objects/Player.h"
#include <unordered_map>
#include <map>
#include "../Define.h"

struct ImageManager {
	
};

class Addon
{
public:
	Addon();
	Addon(std::string addonPath, gobj::Player_Ptr _player);

	bool isActive = true;

	sol::state lua = sol::state();
	gobj::Player_Ptr player;

	std::string rootFolder;
	std::string name;

	std::map<std::string, std::shared_ptr<graphics::Texture>> textures;

	void Init();
	void Setup();
	void Update();
	void Draw();
	void Destroy();

	std::shared_ptr<graphics::Texture> GetOrCreateImage(std::string path);

	void Print(std::string s);

	// context
	void DrawImage(std::shared_ptr<graphics::Texture>, float x, float y, float scale_x, float scale_y, float rotation);
	void DrawRect(float x, float y, float w, float h);
};

