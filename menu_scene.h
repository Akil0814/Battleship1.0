#pragma once
#include "scene_manager.h"
#include "scene.h"
#include"button.h"

extern IMAGE Menu_background;
extern IMAGE Menu_Start_Idle;
extern IMAGE Menu_Start_Hovered;
extern IMAGE Menu_Start_Pushed;
extern IMAGE Menu_Setting_Idle;
extern IMAGE Menu_Setting_Hovered;
extern IMAGE Menu_Setting_Pushed;

extern SceneManager scene_manager;

class MenuScene :public Scene
{
public:
	MenuScene() = default;

	~MenuScene() = default;

	void on_enter()
	{
		WINDOW_WIDTH = Menu_background.getwidth();
		WINDOW_HEIGHT = Menu_background.getheight();
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	}

	void on_update()
	{
		if (setting.cheek_is_clicked())
			scene_manager.switch_to(SceneManager::SceneType::Setting);
		if (LocalPVP.cheek_is_clicked())
			scene_manager.switch_to(SceneManager::SceneType::Local_PVP);

	}

	void on_draw()
	{
		putimage(0, 0, &Menu_background);

	}

	void on_input(const ExMessage& msg)
	{
		LocalPVP.process_event(msg);
	}

	void on_exit()
	{

	}

private:

	Button setting;
	Button PVE;
	Button LocalPVP;
	Button OnlinePVP;

	int space_between_button = 10;
	bool is_click = false;

};
