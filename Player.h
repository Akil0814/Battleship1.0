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
		int def = 0;
		for (int i = 0; i < num_of_ship; i++)
		{
			Ship* new_ship =new Ship;
			new_ship->set_image(&Ship_img[i]);
			new_ship->set_pos(0, def);
			def += 50;
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

	void move_ship(const int x,const int y,const int dx,const int dy)
	{
		current_ship->set_pos(x - dx, y - dy);
	}

	void rotate_current_ship()
	{
		current_ship->rotate_ship();
	}

	void get_current_ship(int x,int y)
	{

		for (int i = 0; i < ship_list.size(); i++)
		{
			if (ship_list[i]->check_cursor_hit(x, y))
				current_ship = ship_list[i];
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
	
	vector<Ship*>ship_list;
	int ship_count;
	bool is_win = false;
	int ship_grid_have = 12;
};