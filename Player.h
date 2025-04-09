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
	~Player() = default;

	void set_ship_img()
	{
		int def = 0;
		ship_list = { ship1,ship2,ship3,ship4,ship5 };
		for (int i = 0; i < ship_list.size(); i++)
		{
			ship_list[i].set_image(&Ship_img[i]);
			ship_list[i].set_pos(0, def);
			def += 50;
		}
	}
	
	void draw_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			ship_list[i].draw();
		}
	}

	void move_ship(int x,int y,int dx,int dy)
	{
		current_ship->set_pos(x - dx, y - dy);
		//current_ship->set_left(x-dx);
		//current_ship->set_top(y-dy);
	}


	void get_current_ship(int x,int y)
	{

		for (int i = 0; i < ship_list.size(); i++)
		{
			if (ship_list[i].check_cursor_hit(x, y))
				current_ship = &ship_list[i];
		}
	}

public:

	Board board;
	Ship* current_ship = &ship1;

private:

	Ship ship1;
	Ship ship2;
	Ship ship3;
	Ship ship4;
	Ship ship5;
	vector<Ship>ship_list;

	bool is_win = false;
	int ship_grid_have = 12;
};