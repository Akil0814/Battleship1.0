#pragma once
#include<vector>
using namespace std;

#define IS_EMPTY 0
#define IS_SHIP 1
#define IS_CHEAKED 2
#define IS_HIT 3

extern IMAGE Base;
extern IMAGE Bar;

class Board
{
public:
	Board() = default;
	~Board() = default;

	void set_board()
	{
		board_see.assign(row, vector<int>(col, IS_EMPTY));
		board_data.assign(row, vector<int>(col, IS_EMPTY));
		board_height = row * base_width;
		board_width = col * base_width;
	}

	void ship_moved(const int size, const bool is_horizontal, const int x, const int y)
	{
		cout << "ship moved" << endl;
		if (x >= col || y >= row || x < 0 || y < 0)
		{
			show_board();
			return;
		}

		std::cout << "not in if" << endl;//test//////////////////////

		if (is_horizontal)
		{
				for (int i = 0; i < size; i++)
				{
					board_data[x + i][y] = IS_EMPTY;
				}
		}
		else
		{
				for (int i = 0; i < size; i++)
				{
					board_data[x][y + i] = IS_EMPTY;
				}
		}
		show_board();////////////////////////////

	}

	bool set_ship(const int size, const bool is_horizontal,const int x,const int y)
	{

		if (x < col && y < row && x>=0 && y>=0)
		{
			if (is_horizontal)
			{
				if (x + size <= col)
				{
					for (int i = 0; i < size; i++)
					{
						board_data[x+i][y] = IS_SHIP;
					}
					show_board();////////////////////////////
					return true;
				}
			}
			else
			{
				if (y + size <= row)
				{
					for (int i = 0; i < size; i++)
					{
						board_data[x][y+i] = IS_SHIP;
					}
					show_board();/////////////////////////////////

					return true;
				}
			}
		}

		return false;
	}

	void draw_setup_board()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				putimage(j * base_width, i * base_width, &Base);
			}
		}
	}

	void draw_player_turn()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_see[i][j])
				{
				case IS_EMPTY:
					putimage(j * base_width + board_width + 30, i * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage(j * base_width + board_width + 30, i * base_width, &Base);
					break;
				case IS_HIT:
					putimage(j * base_width + board_width + 30, i * base_width, &Base);
					break;
				default:
					break;
				}
			}
		}
	}

	void draw_enemy_turn()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_see[i][j])
				{
				case IS_EMPTY:
					putimage(j * base_width, i * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage(j * base_width, i * base_width, &Base);
					break;
				case IS_HIT:
					putimage(j * base_width, i * base_width, &Base);
					break;
				default:
					break;
				}
			}
		}
	}

	void check_hit(int x,int y)
	{
		if (board_data[x][y] == IS_SHIP && board_see[x][y] == IS_EMPTY)
		{
			board_see[x][y] = IS_HIT;
			board_data[x][y] = IS_HIT;
		}
		if (board_data[x][y] == IS_EMPTY && board_see[x][y] == IS_EMPTY)
		{
			board_see[x][y] = IS_CHEAKED;
		}
	}


	int get_width()const
	{
		return board_width;
	}

	int get_height()const
	{
		return board_height;
	}

	void show_board()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << board_data[j][i] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

private:
	vector<vector<int>>board_see;
	vector<vector<int>>board_data;

	int row = 10;
	int col = 10;

	int board_height = 0;
	int board_width= 0;

	int base_width = 50;
};
