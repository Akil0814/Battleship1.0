#pragma once
#include"board.h"

class Player
{
public:
	Player() = default;
	~Player() = default;
public:
	Board board;
private:
	bool is_win = false;
	int ship_grid_have = 12;
};