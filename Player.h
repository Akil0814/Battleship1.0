#pragma once
#include<vector>
#include"board.h"
#include"ship.h"

using namespace std;

extern IMAGE Ship_img[5];

class Player
{
public:
	Player() = default;
	~Player()
	{
		delete_all_ship();
	}

	void set_ship_img()
	{
		delete_all_ship();
		for (int i = 0; i < num_of_ship; i++)
		{
			Ship* new_ship =new Ship;
			new_ship->set_image(&Ship_img[i]);
			new_ship->set_pos(0,board.get_height());
			new_ship->set_index(0, 10);
			ship_list.push_back(new_ship);
		}
	}
	
	void draw_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			ship_list[i]->draw();
		}
	}

	void get_current_ship(int x, int y)
	{

		for (int i = 0; i < ship_list.size(); i++)
		{
			if (ship_list[i]->check_cursor_hit(x, y))
			{
				current_ship = ship_list[i];
			}
		}
	}

	void rotate_current_ship()
	{
		if (current_ship->get_ship_pos_index_y() == 10)//will not rotate if ship is out of board
			return;

		board.ship_moved(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship->get_ship_pos_index_x(), current_ship->get_ship_pos_index_y());//take ship out from the board
		current_ship->rotate_ship();
		
		if (!board.set_ship(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship->get_ship_pos_index_x(), current_ship->get_ship_pos_index_y()))
		{
			current_ship->rotate_ship();
			board.set_ship(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship->get_ship_pos_index_x(), current_ship->get_ship_pos_index_y());
		}
	}

	void move_ship(const int x,const int y)
	{
		if (!ship_is_moving)
		{
			board.ship_moved(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship->get_ship_pos_index_x(), current_ship->get_ship_pos_index_y());
			dx = x - current_ship->get_left();
			dy = y - current_ship->get_top();

			ship_is_moving = true;
		}
		current_ship->set_pos(x - dx, y - dy);
	}

	void put_current_ship()
	{
		ship_is_moving = false;

		current_ship_move_to_index_y = current_ship->get_top() / size_of_base;


		if (current_ship->get_top() % size_of_base > size_of_base / 2)
			current_ship_move_to_index_y++;


		current_ship_move_to_index_x = current_ship->get_left() / size_of_base;
		if (current_ship->get_left() % size_of_base > size_of_base / 2)
			current_ship_move_to_index_x++;


		if (board.set_ship(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship_move_to_index_x, current_ship_move_to_index_y))//will retrurn fales if pos is not avilable
		{
			current_ship->set_pos(current_ship_move_to_index_x * size_of_base, current_ship_move_to_index_y * size_of_base);
			current_ship->set_index(current_ship_move_to_index_x, current_ship_move_to_index_y);
		}
		else
		{
			current_ship->set_pos(current_ship->get_ship_pos_index_x() * size_of_base, current_ship->get_ship_pos_index_y() * size_of_base);
			board.set_ship(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship->get_ship_pos_index_x(), current_ship->get_ship_pos_index_y());
		}

	}

	void delete_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			delete ship_list[i];
		}

		ship_list.clear();
	}

public:
	Board board;
	Ship* current_ship = nullptr;

private:
	int num_of_ship = 5;
	int size_of_base = 50;

	int dx = 0;
	int dy = 0;

	int current_ship_move_to_index_x = 0;
	int current_ship_move_to_index_y = 0;
	
	vector<Ship*>ship_list;
	bool ship_is_moving=false;
	bool is_win = false;
	int ship_grid_have = 12;
};