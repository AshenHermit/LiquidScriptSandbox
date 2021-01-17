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

		std::unordered_map<std::string, bool> var_bool;
		std::unordered_map<std::string, float> var_num;
		std::unordered_map<std::string, std::string> var_str;
			
		std::vector<std::shared_ptr<Addon>> addons;

		std::unordered_map<std::string, bool> isPressed;
		std::unordered_map<std::string, bool> onPress;

		void Init();
		void Update();
		void Draw();

		void InitAddons();
		void DestroyAddons();
		void LoadAddons(Player_Ptr self);

		bool IsPressed(std::string key);
		bool OnPress(std::string key);

		// vars

		bool GetBool(std::string key);
		float GetNum(std::string key);
		std::string GetStr(std::string key);

		void SetBool(std::string key, bool value);
		void SetNum(std::string key, float value);
		void SetStr(std::string key, std::string value);
	};

	typedef std::shared_ptr<Player> Player_Ptr;
}

