//~2000 line
#include<graphics.h>
#include<iostream>
#include <memory>

#include"scene_manager.h"

#include"scene.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"game_end_scene.h"
#include"setup_scene.h"
#include"local_pvp_scene.h"
#include"pve_scene.h"

#include"button.h"

#include"board.h"
#include"ship.h"

#include"player.h"
#include"computer_player.h"
#include"human_player.h"

ExMessage msg;

IMAGE Menu_background;

IMAGE Menu_Local_PVP_Idle;
IMAGE Menu_Local_PVP_Hovered;
IMAGE Menu_Local_PVP_Pushed;

IMAGE Menu_PVE_Idle;
IMAGE Menu_PVE_Hovered;
IMAGE Menu_PVE_Pushed;

IMAGE Menu_Setting_Idle;
IMAGE Menu_Setting_Hovered;
IMAGE Menu_Setting_Pushed;

IMAGE Setup_next_Idle;
IMAGE Setup_next_Hovered;
IMAGE Setup_next_Pushed;

IMAGE Base;
IMAGE Hit;
IMAGE Miss;

IMAGE Ship_img[5];

Scene* menu_scene = nullptr;
Scene* setting_scene = nullptr;
Scene* setup_scene = nullptr;
Scene* PVE_scene = nullptr;
Scene* online_PVP_scene = nullptr;
Scene* local_PVP_scene = nullptr;
Scene* game_end_scene = nullptr;

SceneManager scene_manager;

Player* player1 = nullptr;
Player* player2 = nullptr;
Player* current_player = nullptr;

void LoadResource()
{
	loadimage(&Menu_background, _T("res/Menu_back_ground.png"));

	loadimage(&Menu_Setting_Idle, _T("res/Menu_Setting_Idle.png"));
	loadimage(&Menu_Setting_Hovered, _T("res/Menu_Setting_Hovered.png"));
	loadimage(&Menu_Setting_Pushed, _T("res/Menu_Setting_Pushed.png"));

	loadimage(&Menu_Local_PVP_Hovered, _T("res/Menu_Local_PVP_Hovered.png"));
	loadimage(&Menu_Local_PVP_Idle, _T("res/Menu_Local_PVP_Idle.png"));
	loadimage(&Menu_Local_PVP_Pushed, _T("res/Menu_Local_PVP_Pushed.png"));

	loadimage(&Menu_PVE_Hovered, _T("res/Menu_PVE_Hovered.png"));
	loadimage(&Menu_PVE_Idle, _T("res/Menu_PVE_Idle.png"));
	loadimage(&Menu_PVE_Pushed, _T("res/Menu_PVE_Pushed.png"));

	loadimage(&Base, _T("res/Base.png"));
	loadimage(&Hit, _T("res/Hit.png"));
	loadimage(&Miss, _T("res/Miss.png"));


	loadimage(&Ship_img[0], _T("res/Ship1.png"));
	loadimage(&Ship_img[1], _T("res/Ship2.png"));
	loadimage(&Ship_img[2], _T("res/Ship3.png"));
	loadimage(&Ship_img[3], _T("res/Ship4.png"));
	loadimage(&Ship_img[4], _T("res/Ship5.png"));


	loadimage(&Setup_next_Idle, _T("res/Setup_next_Idle.png"));
	loadimage(&Setup_next_Hovered, _T("res/Setup_next_Hovered.png"));
	loadimage(&Setup_next_Pushed, _T("res/Setup_next_Pushed.png"));
}

int main()
{
	constexpr int FPS = 60;

	srand((unsigned int)time(NULL));

	LoadResource();
	initgraph(10, 10);
	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_end_scene = new GameEndScene();
	player1 = new HumanPlayer();

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

	delete menu_scene;
	delete game_end_scene;
	delete player1;

	return 0;
}