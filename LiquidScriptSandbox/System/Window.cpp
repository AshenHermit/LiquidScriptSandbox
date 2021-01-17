#include "Window.h"
#include "Console.h"
#include "Global.h"
#include <iostream>
#include "../ImGui/imgui_impl_opengl3.h"

using namespace sys;

void error_callback(int error, const char* msg) {
	std::string s;
	s = " [" + std::to_string(error) + "] " + msg + '\n';
	std::cerr << s << std::endl;
}

Window::Window(std::string title, int width, int height)
{
	InitGLFW();
	InitWindow(title, width, height);
	InitGLAD();
	InitOpenGL(width, height);

	InitImGUI();
}

sys::Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}

void sys::Window::InitImGUI()
{
	ImGui::CreateContext();
	io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}

void sys::Window::InitGLFW()
{
	glfwSetErrorCallback(error_callback);

	// setup glfw
	if (!glfwInit()) {
		_console_error("Failed to initalize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void sys::Window::InitWindow(std::string& title, int& width, int& height)
{
	// create glfw window
	glfw_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (glfw_window == NULL) {
		_console_error("Failed to create GLFW window");
		glfwTerminate();
	}

	// activating gl context
	glfwMakeContextCurrent(glfw_window);

	glfwSetFramebufferSizeCallback(glfw_window, on_resize);
}

void sys::Window::InitGLAD()
{
	// initalizing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		_console_error("Failed to initalize GLAD");
	}
}

void sys::Window::InitOpenGL(int& width, int& height)
{
	glViewport(0, 0, width, height);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void sys::Window::PollEvents()
{
	glfwPollEvents();

	if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(glfw_window, true);
	}
}

void sys::Window::Clear()
{
	ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT);
}

void sys::Window::StartUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void sys::Window::Display()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(glfw_window);
}

bool sys::Window::IsOpen()
{
	return !glfwWindowShouldClose(glfw_window);
}

void sys::Window::on_resize(GLFWwindow*, int width, int height)
{
	global.win_width = width;
	global.win_height = height;
	glViewport(0, 0, width, height);
}
