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

	void draw_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			ship_list[i]->draw();
		}
	}

	void draw_all_ship(bool is_left)
	{
		if (is_left)
		{
			for (int i = 0; i < ship_list.size(); i++)
			{
				ship_list[i]->draw();
			}
		}
		else
		{
			for (int i = 0; i < ship_list.size(); i++)
			{
				ship_list[i]->draw_right();
			}
		}
	}

	void update_board(const int x, const int y)
	{
		board.update_board(x, y);
	}

	bool check_board_available(const int x, const int y)
	{
		return board.check_board(x, y);
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

	void draw_player_board(bool is_left,bool cover_ship)
	{
		if (!cover_ship)
		{
			if (is_left)
				board.draw_player_board_left_end();
			else
				board.draw_player_board_right_end();
		}
		else
		{
			if (is_left)
				board.draw_player_board_left();
			else
				board.draw_player_board_right();
		}

	}

	int check_pos_type(const int x, const int y)const
	{
		return board.get_board_type(x, y);
	}

	void delete_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			delete ship_list[i];
		}

		ship_list.clear();
	}

protected:
	vector<Ship*>ship_list;
	Board board;
	
	int num_of_ship = 5;
	int size_of_base = 50;

	bool is_win = false;
};