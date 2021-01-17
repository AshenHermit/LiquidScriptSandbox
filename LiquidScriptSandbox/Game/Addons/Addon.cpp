#include "Addon.h"
#include "../../System/Global.h"
#include "../../System/Math/Vector2.h"


Addon::Addon()
{

}

Addon::Addon(std::string addonPath, gobj::Player_Ptr _player) : Addon()
{
	rootFolder = addonPath;
	player = _player;
	Setup();
}

void Addon::Init()
{
	lua["Init"]();
}

void Addon::Setup()
{
	// libraries
	lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table);

	// usertypes
	lua.new_usertype<Vector2>("Vector2",
		"x", &Vector2::x,
		"y", &Vector2::y,
		"__add", &Vector2::operator+,
		"__sub", &Vector2::operator-,
		"__mul", (Vector2(Vector2::*)(Vector2)) & Vector2::operator*,
		"__div", (Vector2(Vector2::*)(Vector2)) & Vector2::operator/,
		"mul", &Vector2::Mul,
		"div", &Vector2::Div
	);

	lua.new_usertype<graphics::Texture>("Image",
		"width", &graphics::Texture::width,
		"height", &graphics::Texture::height);

	lua.new_usertype<gobj::Player>("Player",
		"position", &gobj::Player::position,
		"velocity", &gobj::Player::velocity,

		"is_pressed", &gobj::Player::IsPressed,
		"on_press", &gobj::Player::OnPress

		//"get_bool", &gobj::Player::GetBool,
		//"get_num", &gobj::Player::GetNum,
		//"get_str", &Player::GetStr,
		//
		//"set_bool", &Player::SetBool,
		//"set_num", &Player::SetNum,
		//"set_str", &Player::SetStr
	);


	// variables
	lua["player"] = player;



	// addon context containig draw functions and other
	auto ctx = lua["ctx"].get_or_create<sol::table>();
	ctx.set_function("image", &Addon::GetOrCreateImage, this);
	ctx.set_function("draw_image", &Addon::DrawImage, this);

	//ctx.set_function("print", &Addon::Print, this);

	lua.script_file(rootFolder + "\\main.lua");

}

void Addon::Update()
{
	lua["Update"]();
}

void Addon::Draw()
{
	lua["Draw"]();
}

void Addon::Destroy()
{
	lua["Destroy"]();
}

std::shared_ptr<graphics::Texture> Addon::GetOrCreateImage(std::string path) {
	textures[path] = std::shared_ptr<graphics::Texture>(new graphics::Texture(global.requests.Request(path)));
	return textures[path];
}

void Addon::Print(std::string s)
{
	std::cout << s << std::endl;
}

void Addon::DrawImage(std::shared_ptr<graphics::Texture> texture, float x, float y, float scale_x, float scale_y, float rotation)
{
	texture->Use();
	global.gctx_ptr->transfrom = glm::mat4(1.0);
	global.gctx_ptr->transfrom = glm::translate(global.gctx_ptr->transfrom, glm::vec3(x, y, 0.0f));
	global.gctx_ptr->transfrom = glm::rotate(global.gctx_ptr->transfrom, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	global.gctx_ptr->transfrom = glm::scale(global.gctx_ptr->transfrom, glm::vec3(scale_x, scale_y, 1.0f));
	global.gctx_ptr->DrawSquare();
}

void Addon::DrawRect(float x, float y, float scale_x, float scale_y)
{

}
