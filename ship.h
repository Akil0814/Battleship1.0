#pragma once
#include<graphics.h>

class Ship
{
public:
	Ship()
	{

	}
	~Ship()
	{

	}

	bool check_cursor_hit(int x, int y)const
	{
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}

	void set_image(IMAGE* idle)
	{
		img= idle;
	}

	void set_top(int x)
	{
		region.top = x;
		region.bottom = region.top + img->getheight();
	}

	void set_left(int y)
	{
		region.left = y;
		region.right = region.left + img->getwidth();
	}

	void draw()
	{
		putimage(region.left, region.top, img);
	}

	int get_ship_img_width()const
	{
		return img->getwidth();
	}

	int get_ship_img_height()const
	{
		return img->getheight();
	}

	int get_ship_in_game_width()const
	{
		return img->getwidth()/ size_of_base;
	}

	int get_ship_in_game_height()const
	{
		return img->getheight()/ size_of_base;
	}

	int cheek_top() const
	{
		return region.top;
	}

	int cheek_left() const
	{
		return region.left;
	}

private:
	int size_of_base=50;
	RECT region = { 0,0,0,0 };
	IMAGE* img = nullptr;

};
