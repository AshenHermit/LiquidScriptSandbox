#pragma once
#include <string>

#define GLFW_INCLUDE_GLU
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ImGui/imgui_impl_glfw.h"

namespace sys {

	class Window
	{
	public:
		Window(std::string title, int width, int height);
		~Window();


		GLFWwindow* glfw_window;

		ImGuiIO io;

		// methods
		void InitImGUI();
		void InitGLFW();
		void InitWindow(std::string &title, int &width, int &height);
		void InitGLAD();

		void InitOpenGL(int& width, int& height);

		template <typename T>
		void SetKeyCallback(void(T::*)(GLFWwindow*, int, int, int, int));
		void PollEvents();
		void StartUI();
		void Clear();
		void Display();

		// get
		bool IsOpen();

		// handlers
		static void on_resize(GLFWwindow*, int width, int height);
	};

}
