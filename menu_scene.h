#pragma once
#include "scene_manager.h"
#include "scene.h"
#include"setup_scene.h"
#include"local_pvp_scene.h"
#include"pve_scene.h"

extern IMAGE Menu_background;

extern IMAGE Menu_Local_PVP_Idle;
extern IMAGE Menu_Local_PVP_Hovered;
extern IMAGE Menu_Local_PVP_Pushed;

extern IMAGE Menu_PVE_Idle;
extern IMAGE Menu_PVE_Hovered;
extern IMAGE Menu_PVE_Pushed;


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
		button_localPVP.set_position(100, 150);//tmp;

		button_PVE.set_images(&Menu_PVE_Idle, &Menu_PVE_Hovered, &Menu_PVE_Pushed);
		button_PVE.set_position(100, 300);//tmp;
	}

	void on_update()
	{
		if (button_localPVP.is_clicked_now())
		{
			setup_scene = new SetupScene(SceneManager::SceneType::Local_PVP);
			local_PVP_scene = new LocalPvpScene();


			scene_manager.switch_to(SceneManager::SceneType::Setup);
			button_localPVP.reset_click();
		}
		if (button_PVE.is_clicked_now())
		{
			setup_scene = new SetupScene(SceneManager::SceneType::PVE);
			PVE_scene = new PveScene();


			scene_manager.switch_to(SceneManager::SceneType::Setup);
			button_PVE.reset_click();
		}
	}

	void on_draw()
	{
		putimage(0, 0, &Menu_background);
		button_localPVP.draw();
		button_PVE.draw();
	}

	void on_input(const ExMessage& msg)
	{
		button_localPVP.process_event(msg);
		button_PVE.process_event(msg);
	}

	void on_exit()
	{
		button_localPVP.reset_click();
		button_PVE.reset_click();
	}


private:

	Button button_localPVP;
	Button button_PVE;


	int space_between_button = 10;
	bool is_click = false;
};
