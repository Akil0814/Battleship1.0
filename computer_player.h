#pragma once
#include <random>
#include"player.h"

class ComputerPlayer :public Player
{
public:
	void put_ship_randomly()
	{
		std::random_device rd;							// ���������
		std::mt19937 gen(rd());							// ʹ��Mersenne Twister����
		std::uniform_int_distribution<> dis(0,9);    // ���� [0, 9] �ľ��������ֲ�

		for (int i = 0; i < num_of_ship; i++)
		{
			current_ship = ship_list[i];

			current_ship_move_to_index_x = dis(gen);
			current_ship_move_to_index_y = dis(gen);

			while (!board.set_ship(current_ship->get_ship_size(), current_ship->check_if_is_horizontal(), current_ship_move_to_index_x, current_ship_move_to_index_y))
			{
				current_ship_move_to_index_x = dis(gen);
				current_ship_move_to_index_y = dis(gen);
			}
			board.show_board();
		}
	}
};