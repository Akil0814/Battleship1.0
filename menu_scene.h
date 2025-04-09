#pragma once
#include "scene_manager.h"
#include "scene.h"
#include"button.h"

extern IMAGE Menu_background;
extern IMAGE Menu_Local_PVP_Idle;
extern IMAGE Menu_Local_PVP_Hovered;
extern IMAGE Menu_Local_PVP_Pushed;

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

		button_localPVP.set_images(&Menu_Local_PVP_Idle, &Menu_Local_PVP_Hovered, &Menu_Local_PVP_Pushed);
		button_localPVP.set_position(200, 200);//tmp;

	}

	void on_update()
	{
		if (button_localPVP.is_clicked_now())
		{
			std::cout << "按钮被点击，切换场景" << std::endl;
			scene_manager.switch_to(SceneManager::SceneType::Setup);
			button_localPVP.reset_click();
		}
	}

	void on_draw()
	{
		putimage(0, 0, &Menu_background);
		button_localPVP.draw();
	}

	void on_input(const ExMessage& msg)
	{
		button_localPVP.process_event(msg);
	}

	void on_exit()
	{
		button_localPVP.reset_click();
	}

private:

	Button button_localPVP;

	int space_between_button = 10;
	bool is_click = false;
};
