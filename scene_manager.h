#pragma once
#include"scene.h"

extern Scene* menu_scene;
extern Scene* setting_scene;
extern Scene* setup_scene;
extern Scene* PVE_scene;
extern Scene* local_PVP_scene;
extern Scene* online_PVP_scene;
extern Scene* game_end_scene;


class SceneManager
{
public:
	enum class SceneType
	{
		Menu,
		Setting,
		Setup,
		PVE,
		Online_PVP,
		Local_PVP,
		Game_end
	};

public:
	SceneManager() = default;
	~SceneManager() = default;

	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_to(SceneType type)
	{
		current_scene->on_exit();
		switch (type)
		{
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Setting:
			current_scene = setting_scene;
			break;
		case SceneType::Setup:
			current_scene = setup_scene;
			break;
		case SceneType::PVE:
			current_scene = PVE_scene;
			break;
		case SceneType::Online_PVP:
			current_scene = online_PVP_scene;
			break;
		case SceneType::Local_PVP:
			current_scene = local_PVP_scene;
			break;
		case SceneType::Game_end:
			current_scene = game_end_scene;
			break;

		default:
			break;
		}
		current_scene->on_enter();
	}

	void on_update()
	{
		current_scene->on_update();
	}
	
	void on_draw()
	{
		current_scene->on_draw();
	}
	
	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}

private:
	Scene* current_scene = nullptr;
};
