#pragma once
#include<graphics.h>
#define PI 3.14159265359

class Ship
{
public:
	Ship(){}
	~Ship()
	{
		if (rotate_img != nullptr)
			delete rotate_img;
	}

	void set_image(IMAGE* idle)
	{
		original_img = idle;
		rotate_img = new IMAGE(*idle);
		rotateimage(rotate_img, original_img, PI / 2, WHITE, true, true);

		size_of_ship = idle->getwidth()/size_of_base;
		hp = size_of_ship;

		current_img = original_img;
	}

	void set_pos(int x, int y)
	{
		region.left = x;
		ship_pos_x = x;
		region.right = region.left + current_img->getwidth();

		region.top = y;
		ship_pos_y = y;
		region.bottom = region.top + current_img->getheight();
		update_pos();
	}

	void rotate_ship()
	{
		is_horizontal = !is_horizontal;

		is_horizontal ? current_img = original_img : current_img = rotate_img;

		update_pos();
	}

	void draw()
	{
		putimage(region.left, region.top, current_img);
	}

	void place_ship()//
	{
		ship_pos_index_x = region.top / size_of_base;
		if (region.top % size_of_base > size_of_base / 2)
			ship_pos_index_x++;

		ship_pos_index_y = region.left / size_of_base;
		if (region.left % size_of_base > size_of_base / 2)
			ship_pos_index_y++;

		region.top = ship_pos_index_x * size_of_base;
		region.left = ship_pos_index_y * size_of_base;
	}

	void is_hit()
	{
		if (!is_ship_sink)
		{
			hp--;
			if (hp == 0)
				is_ship_sink = true;
		}
	}

	int get_ship_pos_index_x()const{	return ship_pos_index_x; }

	int get_ship_pos_index_y()const {	return ship_pos_index_y; }

	int get_top() const{ return region.top; }

	int get_left() const {	return region.left;}

	int get_ship_size()const	{	return size_of_ship; }

	bool check_if_is_horizontal()const {	return is_horizontal; }

	bool check_if_ship_sink()const { return is_ship_sink; }

	bool check_cursor_hit(int x, int y)const
	{
		return x >= region.left && x <= region.right 
			&& y >= region.top && y <= region.bottom;
	}

private:

	void update_pos()
	{
		region.bottom = region.top + current_img->getheight();
		region.right = region.left + current_img->getwidth();
	}

private:

	int hp = 0;

	int size_of_base=50;

	int size_of_ship = 0;

	int ship_pos_x =0;
	int ship_pos_y = 0;

	int ship_pos_index_x =0;
	int ship_pos_index_y = 0;

	int ship_pos_index_x_memory = 0;
	int ship_pos_index_y_memory = 0;

	bool is_horizontal = true;
	bool is_ship_sink = false;

	RECT region = { 0,0,0,0 };
	IMAGE* current_img = nullptr;
	IMAGE* original_img = nullptr;
	IMAGE* rotate_img = nullptr;
};
