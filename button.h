 #pragma once
#include<graphics.h>

class Button
{
public:
	Button(){}
	~Button() {}

	void set_image(IMAGE* idle, IMAGE* hovered, IMAGE* pushed)
	{
		img_idle = idle;
		img_hovered = hovered;
		img_pushed = pushed;
	}

	void set_top(int x)
	{
		region.top = x;
		region.bottom = region.top + img_idle->getheight();
	}

	void set_left(int y)
	{
		region.left= y;
		region.right = region.left + img_idle->getwidth();
	}

	void set_hold()
	{
		will_hold = true;
	}

	void reset_click()
	{
		is_clicked = false;
	}

	void reset_hold()
	{
		will_hold=false;
	}

	void draw()
	{
		if (will_hold)
		{
			putimage(region.left, region.top, img_pushed);
			return;
		}

		switch (status)
		{
		case Status::Idle:
			putimage(region.left, region.top, img_idle);
			break;
		case Status::Hovered:
			putimage(region.left, region.top, img_hovered);
			break;
		case Status::Pushed:
			putimage(region.left, region.top, img_pushed);
			break;
		}
	}

	void process_event(const ExMessage& msg)
	{

		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (status == Status::Idle && check_cursor_hit(msg.x, msg.y))
				status = Status::Hovered;
			else if (status == Status::Hovered && !check_cursor_hit(msg.x, msg.y))
				status = Status::Idle;
			break;
		case WM_LBUTTONDOWN:
			if (check_cursor_hit(msg.x, msg.y))
			{
				status = Status::Pushed;
			}
			break;
		case WM_LBUTTONUP:
			if (status == Status::Pushed)
			{
				is_clicked = true;
				if(!will_hold)
					status = Status::Idle;
			}
			break;
		default:
			break;
		}
	}

	bool check_cursor_hit(int x, int y)const
	{
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}

	bool cheek_is_clicked()const
	{
		return is_clicked;
	}

	bool cheek_hold()const
	{
		return will_hold;
	}

	int get_button_width()const
	{
		return img_idle->getwidth();
	}

	int get_button_height()const
	{
		return img_idle->getheight();
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

	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:

	bool is_clicked = false;
	bool will_hold = false;

	RECT region={0,0,0,0};
	IMAGE* img_idle=nullptr;
	IMAGE* img_hovered = nullptr;
	IMAGE* img_pushed = nullptr;
	Status status = Status::Idle;
};