#pragma once
#include<graphics.h>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void on_enter() = 0;
	virtual void on_update() = 0;
	virtual void on_draw() = 0;
	virtual void on_input(const ExMessage& msg) = 0;
	virtual void on_exit() = 0;

protected:
	int WINDOW_WIDTH=10;
	int WINDOW_HEIGHT=10;
};