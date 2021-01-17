#pragma once
#include "Window.h"
#include "Graphics/Graphics.h"
#include "RequestManager.h"

namespace sys {
	class Global
	{
	public:
		Global();

		int win_width = 1280;
		int win_height = 720;

		Window* main_window;
		graphics::Graphics* gctx_ptr;
		RequestManager requests;

		std::map<std::string, bool> keyCodes;
	};
}

extern sys::Global global;