#pragma once
#include<vector>
#include <random>

#include"board.h"
#include"ship.h"

using namespace std;

extern IMAGE Ship_img[5];

class Player
{
public:
	Player() = default;
	~Player() = default;

	virtual void setup_ship() = 0;

	virtual void put_ship() = 0;

	bool check_pos_can_hit(const int x,const int y)//const
	{
		if (board.check_board(x, y))
		{
			board.update_board(x, y);
			return true;
		}
		return false;
	}

	int get_ship_count_index_on_board()const
	{
		return board.get_ship_count_index();
	}

	void draw_player_board()
	{
		board.draw_player_board_left();
	}

	void draw_player_board(bool is_left)
	{
		if (is_left)
			board.draw_player_board_left();
		else
			board.draw_player_board_right();
	}

	int check_pos_type(const int x, const int y)const
	{
		return board.get_board_type(x, y);
	}

protected:
	Board board;
	
	int num_of_ship = 5;
	int size_of_base = 50;

	bool is_win = false;
};