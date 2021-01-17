#pragma once
#include "../../System/Resources.h"
#include "../../System/Math/Vector2.h"

#include <unordered_map>
#include <map>
#include <memory>

class Addon;

namespace gobj {
	class Player
	{
	public:
		typedef std::shared_ptr<Player> Player_Ptr;
		Player();
		~Player();

		Vector2 position;
		Vector2 velocity;
			
		std::vector<std::shared_ptr<Addon>> addons;

		std::unordered_map<std::string, bool> isPressed;
		std::unordered_map<std::string, bool> onPress;

		void Init();
		void Update();
		void Draw();
		void LoadAddons(Player_Ptr self);

		bool IsPressed(std::string key);
		bool OnPress(std::string key);
	};

	typedef std::shared_ptr<Player> Player_Ptr;
}

