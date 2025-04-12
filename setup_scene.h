#pragma once
#include "scene_manager.h"
#include "scene.h"

#include"player.h"
#include"human_player.h"
#include"computer_player.h"

#include"button.h"

extern SceneManager scene_manager;
extern Scene* menu_scene;

extern Player* current_player;
extern Player* player1;
extern Player* player2;

extern IMAGE Setup_next_Idle;
extern IMAGE Setup_next_Hovered;
extern IMAGE Setup_next_Pushed;


class SetupScene :public Scene
{
public:
	explicit SetupScene(SceneManager::SceneType target_type) : target_scene(target_type){}

	void on_enter()
	{
		current_player = player1;

		//初始化p1数据

		button_next.set_images(&Setup_next_Idle, &Setup_next_Hovered, &Setup_next_Pushed);
		button_next.set_position(WINDOW_WIDTH - Setup_next_Idle.getwidth() - 10, 550);

		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
		setbkcolor(RGB(128, 128, 128));


		switch (target_scene)
		{
		case SceneManager::SceneType::PVE:
			player2 = new ComputerPlayer();
			break;
		case SceneManager::SceneType::Local_PVP:
			player2 = new HumanPlayer();
			break;
		case SceneManager::SceneType::Online_PVP:
			break;
		default:
			break;
		}
	}

	void on_update()
	{

		if (move_current_ship)
		{
			current_player->move_ship(msg_x, msg_y);
		}

		if (rotate_current_ship)
		{
			if(!move_current_ship)
				current_player->rotate_current_ship();
			rotate_current_ship = false;
		}

		if (button_next.is_clicked_now())
		{
			cout << "current_player->board.get_ship_count_index()=" << current_player->board.get_ship_count_index() << endl;//////test

			if (current_player->board.get_ship_count_index()==17)
			{
				switch (target_scene)
				{
				case SceneManager::SceneType::PVE:
					scene_manager.switch_to(SceneManager::SceneType::PVE);
					break;
				case SceneManager::SceneType::Online_PVP:
					break;
				case SceneManager::SceneType::Local_PVP:
					if (current_player == player2)
					{
						scene_manager.switch_to(SceneManager::SceneType::Local_PVP);
						current_player = player1;
					}
					else
						current_player = player2;
					break;
				default:
					break;
				}
			}

			button_next.reset_click();
		}
	}

	void on_draw()
	{
		draw_tip_text_player();
		button_next.draw();
	}

	void on_input(const ExMessage& msg)
	{
		msg_x = msg.x;
		msg_y = msg.y;


		if(!move_current_ship)
		current_player->get_current_ship(msg_x, msg_y);

		if(msg.message == WM_LBUTTONDOWN)
		{
			if (current_player->current_ship != nullptr && current_player->current_ship->check_cursor_hit(msg_x, msg_y))
				move_current_ship = true;
		}

		if(msg.message == WM_LBUTTONUP)
		{
			if (move_current_ship)
			{
				current_player->put_current_ship();
				move_current_ship = false;
			}
		}

		if (msg.message == WM_RBUTTONDOWN)
		{
			if (current_player->current_ship != nullptr && current_player->current_ship->check_cursor_hit(msg_x, msg_y))
				rotate_current_ship = true;
		}
		button_next.process_event(msg);
	}

	void on_exit()
	{

	}

private:
	void draw_tip_text_player()
	{
		static TCHAR str[32];
		if(current_player==player1)
			_stprintf_s(str, _T("Player 1 setting board"));
		else
			_stprintf_s(str, _T("Player 2 setting board"));
		settextcolor(RGB(0, 0, 0));
		outtextxy(250, 520,str);
	}

private:

	Button button_next;

	SceneManager::SceneType target_scene;

	int space_between_button = 10;

	bool move_current_ship = false;
	bool rotate_current_ship = false;

	int dx = 0;
	int dy = 0;
	int msg_x =0;
	int msg_y = 0;

	int text_x = 300;
	int text_y = 300;
};