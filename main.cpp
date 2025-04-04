#include<graphics.h>
#include<iostream>

#include"scene_manager.h"

#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"

#include"button.h"

ExMessage msg;

IMAGE Menu_background;
IMAGE Menu_Start_Idle;
IMAGE Menu_Start_Hovered;
IMAGE Menu_Start_Pushed;
IMAGE Menu_Setting_Idle;
IMAGE Menu_Setting_Hovered;
IMAGE Menu_Setting_Pushed;

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* setting_scene = nullptr;

SceneManager scene_manager;

void LoadResource()
{
	loadimage(&Menu_background, _T("res/Menu_back_ground.png"));
	loadimage(&Menu_Start_Idle, _T("res/Menu_Start_Idle.png"));
	loadimage(&Menu_Start_Hovered, _T("res/Menu_Start_Hovered.png"));
	loadimage(&Menu_Start_Pushed, _T("res/Menu_Start_Pushed.png"));
	loadimage(&Menu_Setting_Idle, _T("res/Menu_Setting_Idle.png"));
	loadimage(&Menu_Setting_Hovered, _T("res/Menu_Setting_Hovered.png"));
	loadimage(&Menu_Setting_Pushed, _T("res/Menu_Setting_Pushed.png"));

}


int main()
{
	constexpr int FPS = 30;

	srand((unsigned int)time(NULL));

	LoadResource();
	initgraph(10, 10);
	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GameScene();

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