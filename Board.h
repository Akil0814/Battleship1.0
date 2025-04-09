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

private:
	vector<vector<int>>board_see;
	vector<vector<int>>board_data;

	int row = 10;
	int col = 10;

	int board_height = 0;
	int board_width= 0;

	int base_width = 50;
};
