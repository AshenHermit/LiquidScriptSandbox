#include "Resources.h"
#include "../Utils/FileManager.h"

using namespace res;

Resources::Resources()
{
	resourcesDir = "../Resources";
}

void Resources::Init()
{
	LoadTextures();
}

void Resources::LoadTextures()
{
	utils::KeyPathList files = utils::GetKeysAndPaths(resourcesDir + "/textures");
	for (int i = 0; i < (int)files.size(); i++) {
		if (files[i].path.find(".png") != -1 || files[i].path.find(".jpg") != -1) {
			textures[files[i].key] = graphics::Texture();
			textures[files[i].key].LoadFromFile(files[i].path);
		}
	}
}
