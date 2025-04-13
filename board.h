#pragma once
#include<vector>
#pragma comment(lib, "MSIMG32.LIB")
using namespace std;

#define IS_EMPTY 0
#define IS_SHIP 1
#define IS_CHEAKED 2
#define IS_HIT 3

extern IMAGE Base;
extern IMAGE Hit;
extern IMAGE Miss;

class Board
{
public:


	Board() = default;
	~Board() = default;

	void set_board()
	{
		board_data.assign(row, vector<int>(col, IS_EMPTY));
		ship_count_index = 0;
		board_height = row * base_width;
		board_width = col * base_width;
	}

	void ship_moved(const int size, const bool is_horizontal, const int x, const int y)
	{
		if (x >= col || y >= row || x < 0 || y < 0)
		{
			return;
		}

		if (is_horizontal)
		{
				for (int i = 0; i < size; i++)
				{
					if (board_data[x + i][y] == IS_SHIP)
					{
						board_data[x + i][y] = IS_EMPTY;
						ship_count_index--;

					}
				}
		}
		else
		{
				for (int i = 0; i < size; i++)
				{
					if (board_data[x][y+i] == IS_SHIP)
					{
						board_data[x][y + i] = IS_EMPTY;
						ship_count_index--;

					}
				}
		}
		//show_board();//////////////////////////////test

	}

	bool set_ship(const int size, const bool is_horizontal, const int x, const int y)
	{
		if (!(x >= 0 && y >= 0 && x < col && y < row))
			return false;

		if (is_horizontal)
		{
			if (x + size > col)
				return false;  // out of range

			for (int i = 0; i < size; i++)//make shure the board is empty
			{
				if (board_data[x + i][y] == IS_SHIP)
				{
					return false;
				}
			}

			for (int i = 0; i < size; i++)
			{
				board_data[x + i][y] = IS_SHIP;
				ship_count_index++;

			}
			//show_board();//////////////////////////////test
			return true;
		}
		else
		{
			if (y + size > row) return false;

			for (int i = 0; i < size; i++)
			{
				if (board_data[x][y + i] == IS_SHIP)
				{
					return false;
				}
			}

			for (int i = 0; i < size; i++)
			{
				board_data[x][y + i] = IS_SHIP;
				ship_count_index++;
				//cout << "ship index=" << ship_count_index << endl;///////////////////////test
			}

			show_board();//////////////////////////////test
			return true;
		}
		return false;
	}

	void draw_player_board_left()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_data[i][j])
				{
				case IS_EMPTY:
				case IS_SHIP:
					putimage(i * base_width, j * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage(i * base_width, j * base_width, &Miss);
					break;
				case IS_HIT:
					putimage(i * base_width, j * base_width, &Base);
					putimage_alpha(i * base_width, j * base_width, &Hit);
					break;
				default:
					break;
				}
			}
		}
	}

	void draw_player_board_right()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_data[i][j])
				{
				case IS_EMPTY:
				case IS_SHIP:
					putimage((i + 1) * base_width + board_width, j * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage((i + 1) * base_width + board_width, j * base_width, &Miss);
					break;
				case IS_HIT:
					putimage((i + 1) * base_width + board_width, j * base_width, &Base);
					putimage_alpha((i + 1) * base_width + board_width, j * base_width, &Hit);
					break;
				default:
					break;
				}
			}
		}
	}

	void draw_player_board_left_end()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_data[i][j])
				{
				case IS_EMPTY:
					putimage(i * base_width, j * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage(i * base_width, j * base_width, &Miss);
					break;
				case IS_HIT:
					putimage_alpha(i * base_width, j * base_width, &Hit);
					break;
				default:
					break;
				}
			}
		}
	}

	void draw_player_board_right_end()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				switch (board_data[i][j])
				{
				case IS_EMPTY:
					putimage((i + 1) * base_width + board_width, j * base_width, &Base);
					break;
				case IS_CHEAKED:
					putimage((i + 1) * base_width + board_width, j * base_width, &Miss);
					break;
				case IS_HIT:
					putimage_alpha((i + 1) * base_width + board_width, j * base_width, &Hit);
					break;
				default:
					break;
				}
			}
		}
	}

	bool check_board(const int x,const int y)//const
	{
		if (x<0 || x>col || y<0 || y>row)
		{
			return false;
		}

		if (board_data[x][y] == IS_SHIP)
		{
			return true;
		}
		else if (board_data[x][y] == IS_EMPTY)
		{
			return true;
		}

		return false;
	}

	void update_board(const int x,const int y)
	{
		if (board_data[x][y] == IS_SHIP)
		{
			board_data[x][y] = IS_HIT;
			ship_count_index--;
		}
		else if (board_data[x][y] == IS_EMPTY)
		{
			board_data[x][y] = IS_CHEAKED;
		}
	}

	int get_width()const { return board_width; }

	int get_height()const { return board_height;}

	int get_ship_count_index()const { return ship_count_index;}

	int get_board_type(int x, int y)const { return board_data[x][y]; }

	//test
	void show_board()//////////////////////////////test
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
	}//////////////////////////////test

private:
	void putimage_alpha(int dst_x, int dst_y, IMAGE* img)//渲染有透明度的图片
	{
		int w = img->getwidth();
		int h = img->getheight();
		AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
			GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
	}
private:
	vector<vector<int>>board_data;

	int row = 10;
	int col = 10;

	int ship_count_index = 0;

	int board_height = 0;
	int board_width= 0;

	int base_width = 50;
};
