#pragma once
#include <random>
#include"player.h"

class ComputerPlayer :public Player
{
public:
	ComputerPlayer() :gen(rd()), pos(0, 9), bin(0, 1), attack_pos(0,4){}

	void setup_ship()
	{
		board.set_board();
		delete_all_ship();
		ship_size.clear();
		ship_point_list.clear();

		for (int i = 0; i < num_of_ship; i++)
		{
			Ship* new_ship = new Ship;
			new_ship->set_image(&Ship_img[i]);
			int size=Ship_img[i].getwidth()/ size_of_base;
			ship_size.push_back(size);
			ship_list.push_back(new_ship);
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
			ship_list[i]->set_index(index_x, index_y);
			if(!is_horizontal)
				ship_list[i]->rotate_ship();
			board.show_board();
		}
	}

	void check_if_hit_target(int type)
	{
		time_attack++;
		time_try_hit = 0;
		cout<<"time_attack=" << time_attack << endl;//////////////////////////test
		switch (current_strategy)
		{
		case Strategy::Random_hit:
			if (type == IS_SHIP)
			{
				x_first_hit_ship=x_hit;
				y_first_hit_ship=y_hit;
				did_check_other_side = false;
				time_try_to_find_direction = 0;
				ship_point_list.push_back(hit);

				current_strategy = Strategy::Try_find_direction;
			}
			break;

		case Strategy::Try_find_direction:
			if (type == IS_SHIP)
			{
				ship_point_list.push_back(hit);
				current_strategy = Strategy::Check_current_direction;
			}
			break;

		case Strategy::Check_current_direction:
			if (type == IS_SHIP)
			{
				ship_point_list.push_back(hit);
			}
			else if (type == IS_EMPTY && !did_check_other_side)
			{
				change_side_checking();
				x_hit = x_first_hit_ship;
				y_hit = y_first_hit_ship;
			}
			else if (type == IS_EMPTY && did_check_other_side)
			{
				current_strategy = Strategy::Random_hit;

			}
			break;
		default:
			break;
		}
	}

	POINT decide_attack_position()
	{
		time_try_hit++;
		cout << "time try hit=" <<time_try_hit<< endl;/////////////////////////////test
		switch (current_strategy)
		{
		case Strategy::Random_hit:
			get_random_pos();
			break;

		case Strategy::Try_find_direction:
			do
			{
				next_direction();
				try_find_direction();
				time_try_to_find_direction++;
				if (time_try_to_find_direction > 4)
				{
					current_strategy = Strategy::Random_hit;
					get_random_pos();
					break;
				}
			} while (!check_in_range());
			break;

		case Strategy::Check_current_direction:
			check_on_current_direction();
			if (!check_in_range())
			{
				if (!did_check_other_side)
				{
					change_side_checking();
					hit=decide_attack_position();
					return hit;
				}
				current_strategy = Strategy::Random_hit;
				get_random_pos();
			}
			break;

		default:
			break;
		}
		return hit;
	}

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

private:

	void next_direction()
	{
		switch (current_direction)
		{
		case Direction::Up:
			current_direction = Direction::Down;
			break;
		case Direction::Down:
			current_direction = Direction::Right;
			break;
		case Direction::Right:
			current_direction = Direction::Left;
			break;
		case Direction::Left:
			current_direction = Direction::Up;
			break;
		default:
			break;
		}
	}

	bool check_in_range()
	{
		if (hit.x < 0 || hit.x>=10 || hit.y < 0 || hit.y>=10)
			return false;
		return true;
	}

	void get_random_pos()
	{


		if (time_attack > 60|| time_try_hit>1000)
		{
			if (ship_point_list.size())
			{
				check_around_ship();
				return;
			}

			x_hit = pos(gen);
			y_hit = pos(gen);
			hit.x = x_hit;
			hit.y = y_hit;

			return;
		}

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
			hit.x = x_hit;
			hit.y = y_hit-1;
			break;
		case Direction::Down:
			hit.x = x_hit;
			hit.y = y_hit+1;
			break;
		case Direction::Right:
			hit.x = x_hit+1;
			hit.y = y_hit;
			break;
		case Direction::Left:
			hit.x = x_hit-1;
			hit.y = y_hit;
			break;
		default:
			break;
		}
	}

	void check_on_current_direction()
	{
		switch (current_direction)
		{
		case Direction::Up:
			y_hit = y_hit - 1;
			break;
		case Direction::Down:
			y_hit = y_hit + 1;
			break;
		case Direction::Right:
			x_hit = x_hit + 1;

			break;
		case Direction::Left:
			x_hit = x_hit - 1;
			break;
		default:
			break;
		}

		hit.x = x_hit;
		hit.y = y_hit;
	}

	void change_side_checking()
	{
		switch (current_direction)
		{
		case Direction::Up:
			current_direction = Direction::Down;
			break;
		case Direction::Down:
			current_direction = Direction::Up;
			break;
		case Direction::Right:
			current_direction = Direction::Left;
			break;
		case Direction::Left:
			current_direction = Direction::Right;
			break;
		default:
			break;
		}
		did_check_other_side = true;
	}

	void check_around_ship()
	{
		int index = 0;
		do
		{
			if (ship_point_list.size() == 0)
				return;

			index= ship_point_list.size() - 1;
			hit=ship_point_list[index];

			switch (time_look_around)
			{
			case 0:
				hit.y = hit.y - 1;
				time_look_around++;
				break;
			case 1:
				hit.y = hit.y +1;
				time_look_around++;
				break;
			case 2:
				hit.x = hit.x - 1;
				time_look_around++;
				break;
			case 3:
				hit.x = hit.x + 1;
				time_look_around++;
				break;
			case 4:
					ship_point_list.pop_back();
					time_look_around = 0;
				break;
			default:
				break;
			}

		} while (!check_in_range());

	}


private:

	std::random_device rd;							// 随机数种子
	std::mt19937 gen;							// 使用Mersenne Twister引擎
	std::uniform_int_distribution<> pos;    // 区间 [0, 9] 的均匀整数分布
	std::uniform_int_distribution<> bin;    // 区间 [0, 2] 的均匀整数分布
	std::uniform_int_distribution<> attack_pos;// 区间 [0, 4] 的均匀整数分布

private:
	POINT hit = {0};
	Strategy current_strategy = Strategy::Random_hit;
	Direction current_direction=Direction::Up;

	int x_hit = 0;
	int y_hit = 0;

	int x_first_hit_ship = 0;
	int y_first_hit_ship = 0;

	bool did_check_other_side = false;

	int time_try_to_find_direction = 0;

	int time_look_around = 0;

	int time_attack=0;

	int time_try_hit = 0;

	vector<int>ship_size;
	vector<POINT>ship_point_list;

};