#pragma once
#include <random>
#include"player.h"



class ComputerPlayer :public Player
{
private:
	enum class Strategy
	{
		Random_hit,
		Try_find_direction,
		Check_current_direction,
		Check_around_ship
	};

	enum class Direction
	{
		Up,
		Down,
		Right,
		Left
	};
public:
	ComputerPlayer() :gen(rd()), pos(0, 9), bin(0, 1), attack_pos(0,4){}

	void setup_ship()
	{
		board.set_board();
		ship_size.clear();

		for (int i = 0; i < num_of_ship; i++)
		{
			int size=Ship_img[i].getwidth()/ size_of_base;
			ship_size.push_back(size);
		}
	}

	void put_ship()
	{
		for (int i = 0; i < num_of_ship; i++)
		{
			int size=ship_size[i];

			int index_x = pos(gen);
			int index_y = pos(gen);
			int is_horizontal = bin(gen);
			while (!board.set_ship(ship_size[i], is_horizontal, index_x, index_y))
			{
				index_x = pos(gen);
				index_y = pos(gen);
				is_horizontal = bin(gen);
			}
			board.show_board();
		}
	}

	void check_if_hit_target(int type)
	{
		time_attack++;
		switch (current_strategy)
		{
		case Strategy::Random_hit:
			if (type == IS_HIT)
			{
				current_strategy = Strategy::Try_find_direction;
				time_hit_the_ship++;
			}
			break;
		case Strategy::Try_find_direction:
			if (type == IS_HIT)
			{
				current_strategy = Strategy::Check_current_direction;
				time_hit_the_ship++;
			}
			break;
		case Strategy::Check_current_direction:
			if (type == IS_HIT)
			{
				time_hit_the_ship++;
			}
			break;
		default:
			break;
		}
	}

	void check_in_range()
	{
		if(hit.x<0|| hit.x>10|| hit.y < 0 || hit.y>10)
		find_direction = false;
	}

	POINT decide_attack_position()
	{
		switch (current_strategy)
		{
		case Strategy::Random_hit:
			get_random_pos();
			break;
		case Strategy::Try_find_direction:
			try_find_direction();
			break;
		case Strategy::Check_current_direction:
			check_on_current_direction();
			current_strategy = Strategy::Random_hit;
			break;
		default:
			break;
		}
		return hit;
	}



private:

	void get_random_pos()
	{
		int is_both_even = bin(gen);

		if (is_both_even)
		{
			x_hit = attack_pos(gen) * 2;
			y_hit = attack_pos(gen) * 2;
		}
		else
		{
			x_hit = attack_pos(gen) * 2 + 1;
			y_hit = attack_pos(gen) * 2 + 1;
		}
		hit.x = x_hit;
		hit.y = y_hit;
	}

	void try_find_direction()
	{
		switch (current_direction)
		{
		case Direction::Up:
			break;
		case Direction::Down:
			break;
		case Direction::Right:
			break;
		case Direction::Left:
			break;
		default:
			cout << "out of switch" << endl;
			break;
			}
	}

	void check_on_current_direction()
	{


			hit.x = x_hit;
			hit.y = y_hit;

	}
private:

	std::random_device rd;							// 随机数种子
	std::mt19937 gen;							// 使用Mersenne Twister引擎
	std::uniform_int_distribution<> pos;    // 区间 [0, 9] 的均匀整数分布
	std::uniform_int_distribution<> bin;    // 区间 [0, 9] 的均匀整数分布
	std::uniform_int_distribution<> attack_pos;

private:

	POINT hit;
	Strategy current_strategy = Strategy::Random_hit;
	Direction current_direction=Direction::Up;

	int x_hit = 0;
	int y_hit = 0;
	int time_hit_the_ship = 0;

	int time_attack=0;


	bool hit_target = false;
	bool find_direction = false;

	vector<int>ship_size;
};