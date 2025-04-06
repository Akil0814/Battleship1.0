#pragma once
#include<vector>
using namespace std;

#define IS_EMPTY 0
#define IS_SHIP 1
#define IS_CHEAKED 2
#define IS_FIND 3
#define IS_SHIP_HIT 4

extern IMAGE Base;

class Board
{
public:
	Board() = default;
	~Board() = default;

	void draw_player_board()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				
				if (board_player_see[i][j] == IS_EMPTY)
				{
					putimage(j * base_width, i * base_width, &Base);
				}
			}
		}
	}


	void set_board()
	{
		board_player_see.assign(row, vector<int>(col, IS_EMPTY));
		board_enemy_see.assign(row, vector<int>(col, IS_EMPTY));
	}

	void set_rows(int s_row)
	{
		row = s_row;
	}

	void set_cols(int s_col)
	{
		col = s_col;
	}

	int cheek_col()const
	{
		return col;
	}

	int cheek_row()const
	{
		return row;
	}

	int get_width()const
	{
		return col* base_width;
	}

	int get_height()const
	{
		return row * base_width;
	}

private:
	vector<vector<int>>board_player_see;
	vector<vector<int>>board_enemy_see;

	int row = 10;
	int col = 10;
	int base_width = 50;
};
