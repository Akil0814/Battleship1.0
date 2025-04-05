#include<graphics.h>
#include<iostream>

#include"scene_manager.h"

#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"local_PVP_setup_scene.h"

#include"button.h"
#include"board.h"
#include"ship.h"
#include"player.h"

ExMessage msg;

IMAGE Menu_background;
IMAGE Menu_Local_PVP_Idle;
IMAGE Menu_Local_PVP_Hovered;
IMAGE Menu_Local_PVP_Pushed;
IMAGE Menu_Setting_Idle;
IMAGE Menu_Setting_Hovered;
IMAGE Menu_Setting_Pushed;

IMAGE Bar;
IMAGE Base;


Scene* menu_scene = nullptr;
Scene* Local_PVP_scene = nullptr;
Scene* Local_PVP_Setup_scene=nullptr;
Scene* setting_scene = nullptr;

SceneManager scene_manager;

Player P1;
Player P2;
Player* current_player = nullptr;

void LoadResource()
{
	loadimage(&Menu_background, _T("res/Menu_back_ground.png"));

	loadimage(&Bar, _T("res/Bar.png"));
	loadimage(&Base, _T("res/Base.png"));

	loadimage(&Menu_Setting_Idle, _T("res/Menu_Setting_Idle.png"));
	loadimage(&Menu_Setting_Hovered, _T("res/Menu_Setting_Hovered.png"));
	loadimage(&Menu_Setting_Pushed, _T("res/Menu_Setting_Pushed.png"));
	loadimage(&Menu_Local_PVP_Hovered, _T("res/Menu_Local_PVP_Hovered.png"));
	loadimage(&Menu_Local_PVP_Idle, _T("res/Menu_Local_PVP_Idle.png"));
	loadimage(&Menu_Local_PVP_Pushed, _T("res/Menu_Local_PVP_Pushed.png"));

}


int main()
{
	constexpr int FPS = 30;

	srand((unsigned int)time(NULL));

	LoadResource();
	initgraph(10, 10);
	BeginBatchDraw();

	menu_scene = new MenuScene();
	//Local_PVP_scene =new LocalPVPScene();
	Local_PVP_Setup_scene=new LocalPVPSetupScene();

	scene_manager.set_current_scene(menu_scene);

	while (true)
	{
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		scene_manager.on_update();

		cleardevice();

		scene_manager.on_draw();

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}

	EndBatchDraw();

	return 0;
}