#pragma once
#include "scene_manager.h"
#include "scene.h"
#include"button.h"

extern IMAGE Menu_background;
extern IMAGE Menu_Local_PVP_Idle;
extern IMAGE Menu_Local_PVP_Hovered;
extern IMAGE Menu_Local_PVP_Pushed;
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

		LocalPVP.set_image(&Menu_Local_PVP_Idle, &Menu_Local_PVP_Hovered, &Menu_Local_PVP_Pushed);
		LocalPVP.set_top((WINDOW_HEIGHT - LocalPVP.get_button_height()) / 2);
		LocalPVP.set_left((WINDOW_WIDTH - LocalPVP.get_button_width()) / 2);

	}

	void on_update()
	{
		if (LocalPVP.cheek_is_clicked())
			scene_manager.switch_to(SceneManager::SceneType::Local_PVP_Setup);
	}

	void on_draw()
	{
		putimage(0, 0, &Menu_background);
		LocalPVP.draw();
	}

	void on_input(const ExMessage& msg)
	{
		LocalPVP.process_event(msg);
	}

	void on_exit()
	{
		LocalPVP.reset_click();
	}

private:

	Button setting;
	Button LocalPVP;

	int space_between_button = 10;
	bool is_click = false;
};
