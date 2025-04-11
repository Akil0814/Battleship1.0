#pragma once
#include"player.h"

class HumanPlayer : public Player
{
public:

	void draw_all_ship()
	{
		for (int i = 0; i < ship_list.size(); i++)
		{
			ship_list[i]->draw();
		}
	}

};