#pragma once
#include <unordered_map>
#include "Graphics/Graphics.h"

namespace res {
	class Resources
	{
	public:
		Resources();

		std::string resourcesDir;

		std::unordered_map<std::string, graphics::Texture> textures;

		void Init();
		void LoadTextures();
	};
};
