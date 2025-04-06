#pragma once
#include "scene_manager.h"
#include "scene.h"

#include"player.h"
#include"button.h"

extern SceneManager scene_manager;
extern Player* current_player;
extern Player P1;
extern Player P2;

extern IMAGE Bar;
extern IMAGE Restart_Idle;
extern IMAGE Restart_Hovered;
extern IMAGE Restart_Pushed;


class LocalPVPSetupScene :public Scene
{
	void on_enter()
	{
		current_player = &P1;

		WINDOW_WIDTH = P1.board.get_width();
		WINDOW_HEIGHT = P1.board.get_height() + Bar.getheight();
		initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

		next.set_image(&Restart_Idle, &Restart_Hovered, &Restart_Pushed);
		next.set_left(WINDOW_WIDTH - next.get_button_width() - space_between_button);
		next.set_top(WINDOW_HEIGHT - next.get_button_height() - space_between_button);

		P1.board.set_board();
		P2.board.set_board();
		P1.set_ship_img();
		P2.set_ship_img();

	}

	void on_update()
	{
		if (next.cheek_is_clicked())
			current_player = &P2;

		if (move_current_ship)
		{
			current_player->move_ship(msg_x, msg_y,dx,dy);

		}
		if (rotate_current_ship)
		{
			current_player->current_ship->rotate_ship();
			current_player->current_ship->update_pos();
			rotate_current_ship = false;
		}
	}

	void on_draw()
	{
		current_player->board.draw_player_board();
		current_player->draw_all_ship();
		putimage(0, P1.board.get_height(),& Bar);
		next.draw();
	}

	void on_input(const ExMessage& msg)
	{
		msg_x = msg.x;
		msg_y = msg.y;

		next.process_event(msg);

		if(!move_current_ship)
		current_player->get_current_ship(msg_x, msg_y);

		if(msg.message == WM_LBUTTONDOWN)
		{
			if (current_player->current_ship->check_cursor_hit(msg_x, msg_y))
			{
				move_current_ship = true;
				dx = msg_x - current_player->current_ship->cheek_left();
				dy = msg_y - current_player->current_ship->cheek_top();
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
		next.reset_click();
	}

private:
	Button next;

	int timer_for_test = 0;/////////////////////////////////////////////////test code

	int space_between_button = 10;

	bool move_current_ship = false;
	bool rotate_current_ship = false;

	int dx = 0;
	int dy = 0;
	int msg_x =0;
	int msg_y = 0;

};