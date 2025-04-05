#pragma once
#include "scene_manager.h"
#include "scene.h"
#include"player.h"
#include"button.h"

extern SceneManager scene_manager;
extern Player* current_player;
extern Player P1;
extern Player P2;


class LocalPVPSetupScene :public Scene
{
	void on_enter()
	{
		current_player = &P1;

		WINDOW_WIDTH = P1.board.get_width();
		WINDOW_HEIGHT = P1.board.get_height();
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
		P1.board.set_board();
		P2.board.set_board();
	}
	void on_update()
	{
	}
	void on_draw()
	{
		current_player->board.draw_player_board();
	}
	void on_input(const ExMessage& msg)
	{

	}
	void on_exit()
	{

	}
};