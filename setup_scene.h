#pragma once
#include "scene_manager.h"
#include "scene.h"

#include"player.h"
#include"button.h"

extern SceneManager scene_manager;
extern Scene* menu_scene;

extern Player* current_player;
extern Player P1;
extern Player P2;
extern Player Computer;

extern IMAGE Bar;
extern IMAGE Restart_Idle;
extern IMAGE Restart_Hovered;
extern IMAGE Restart_Pushed;


class SetupScene :public Scene
{
public:
	explicit SetupScene(SceneManager::SceneType target_type) : target_scene(target_type){}

	void on_enter()
	{
		current_player = &P1;
		P1.board.set_board();
		P1.set_ship_img();

		WINDOW_WIDTH = P1.board.get_width();
		WINDOW_HEIGHT = P1.board.get_height() + Bar.getheight();
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
		switch (target_scene)
		{
		case SceneManager::SceneType::PVE:
			Computer.board.set_board();
			Computer.set_ship_img();
			break;
		case SceneManager::SceneType::Online_PVP:
			break;
		case SceneManager::SceneType::Local_PVP:
			P2.board.set_board();
			P2.set_ship_img();
			break;
		default:
			break;
		}
	}

	void on_update()
	{

		if (move_current_ship)
		{
			current_player->move_ship(msg_x, msg_y,dx,dy);

		}
		if (rotate_current_ship)
		{
			current_player->rotate_current_ship();
			rotate_current_ship = false;
		}
		if (button_next.is_clicked_now())
		{
			switch (target_scene)
			{
			case SceneManager::SceneType::PVE:
				scene_manager.switch_to(SceneManager::SceneType::PVE);
				break;
			case SceneManager::SceneType::Online_PVP:
				break;
			case SceneManager::SceneType::Local_PVP:
				if(current_player==&P2)
					scene_manager.switch_to(SceneManager::SceneType::Local_PVP);
				current_player = &P2;
				break;
			default:
				break;
			}
		}
	}

	void on_draw()
	{
		current_player->board.draw_setup_board();
		current_player->draw_all_ship();
		putimage(0, P1.board.get_height(),& Bar);

	}

	void on_input(const ExMessage& msg)
	{
		msg_x = msg.x;
		msg_y = msg.y;


		if(!move_current_ship)
		current_player->get_current_ship(msg_x, msg_y);

		if(msg.message == WM_LBUTTONDOWN)
		{
			if (current_player->current_ship->check_cursor_hit(msg_x, msg_y))
			{
				move_current_ship = true;
				dx = msg_x - current_player->current_ship->get_left();
				dy = msg_y - current_player->current_ship->get_top();
			}
		}

		if(msg.message == WM_LBUTTONUP)
		{
			move_current_ship = false;
			current_player->current_ship->place_ship();
		}

		if (msg.message == WM_RBUTTONDOWN)
		{
			if (current_player->current_ship->check_cursor_hit(msg_x, msg_y))
				rotate_current_ship = true;
		}
	}

	void on_exit()
	{

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

};