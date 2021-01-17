#pragma once
#include <vector>
#include <memory>
#include "Objects/Player.h"
#include "../System/Graphics/Graphics.h"
#include "../System/Resources.h"

class Game
{
public:
	Game();
	~Game();

	gobj::Player_Ptr localPlayer;
	std::vector<gobj::Player_Ptr> players;

	graphics::Graphics gctx;
	res::Resources resources;

	void ProcessEvents();

	void Init();
	void Update();
	void Draw();

	void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
};


