#pragma once
#include <graphics.h>

class Button
{
public:
	Button() = default;
	~Button() = default;

	void set_images(IMAGE* idle, IMAGE* hovered, IMAGE* pushed)
	{
		img_idle = idle;
		img_hovered = hovered;
		img_pushed = pushed;
	}

	void set_position(int x, int y)
	{
		region.left = x;
		region.top = y;
		if (img_idle)
		{
			region.right = x + img_idle->getwidth();
			region.bottom = y + img_idle->getheight();
		}
	}

	void reset_click()
	{
		is_clicked = false;
	}

	void draw()
	{
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
			status = check_cursor_hit(msg.x, msg.y) ? Status::Hovered : Status::Idle;
			break;
		case WM_LBUTTONDOWN:
			if (check_cursor_hit(msg.x, msg.y))
				status = Status::Pushed;
			break;
		case WM_LBUTTONUP:
			if (status == Status::Pushed)
			{
				if (check_cursor_hit(msg.x, msg.y))
					is_clicked = true;
				status = Status::Idle;
			}
			break;
		}
	}

	bool check_cursor_hit(int x, int y) const
	{
		return x >= region.left && x <= region.right &&
			y >= region.top && y <= region.bottom;
	}

	bool is_clicked_now() const { return is_clicked; }
	bool is_hovered() const { return status == Status::Hovered; }

	int get_width() const { return img_idle ? img_idle->getwidth() : 0; }
	int get_height() const { return img_idle ? img_idle->getheight() : 0; }
	int get_top() const { return region.top; }
	int get_left() const { return region.left; }

private:
	enum class Status { Idle, Hovered, Pushed };

	RECT region{ 0, 0, 0, 0 };
	IMAGE* img_idle = nullptr;
	IMAGE* img_hovered = nullptr;
	IMAGE* img_pushed = nullptr;
	Status status = Status::Idle;
	bool is_clicked = false;
};