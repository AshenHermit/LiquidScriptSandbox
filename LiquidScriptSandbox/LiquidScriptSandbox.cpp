#include <iostream>

#include "Utils/ExceptionTranslator.h"

#include "System/Window.h"
#include "System/Global.h"
#include "Game/Game.h"

#include "System/Graphics/Graphics.h"
#include "System/Graphics/Shader.h"



sys::Global global;

// creating glfw window with title, default size
sys::Window window = sys::Window("Liquid Script Sandbox", global.win_width, global.win_height);

Game game;

void Init() {
	global.main_window = &window;
	global.gameInstance = &game;

	glfwSetKeyCallback(global.main_window->glfw_window, Game::key_callback);

	game.Init();
}

void MainLoop() {

	while (window.IsOpen()) {
		window.PollEvents();
		game.ProcessEvents();

		// update
		game.Update();

		//ui
		window.StartUI();
		game.UpdateUI();

		window.Clear();

		// draw
		game.Draw();

		window.Display();
	}

}

int main()
{
	Scoped_SE_Translator scoped_se_translator{ se_trans_func };
	Init();
	MainLoop();

	return 0;
}

