#pragma once
#include"scene.h"

extern Scene* menu_scene;
extern Scene* setting_scene;
extern Scene* Local_PVP_scene;
extern Scene* Local_PVP_Setup_scene;
//extern Scene* PVE_scene;
//extern Scene* PVE_Setup_scene;
//extern Scene* Online_PVP_scene;
//extern Scene* Online_PVP_Setup_scene;



class SceneManager
{
public:
	enum class SceneType
	{
		Menu,
		Setting,
		PVE,
		PVE_Setup,
		Online_PVP,
		Online_PVP_Setup,
		Local_PVP,
		Local_PVP_Setup,
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
		case SceneType::Local_PVP:
			current_scene = Local_PVP_scene;
			break;
		case SceneType::Local_PVP_Setup:
			current_scene = Local_PVP_Setup_scene;
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
