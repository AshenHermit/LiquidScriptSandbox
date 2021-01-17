#include <iostream>

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

		ImGui::Begin("Another Window");
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Say something"))
			std::cout << "you smell good" << std::endl;
		ImGui::End();

		window.Clear();

		// draw
		game.Draw();

		game.gctx.DrawSquare();

		window.Display();
	}

}

int main()
{
	Init();
	MainLoop();

	return 0;
}

