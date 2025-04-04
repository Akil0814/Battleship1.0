#pragma once

#include "scene_manager.h"
#include "scene.h"
#include"button.h"

extern SceneManager scene_manager;

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{

	}

	void on_update()
	{

	}

	void on_draw()
	{


	}

	void on_input(const ExMessage& msg)
	{

	}

	void on_exit()
	{

	}


private:


};