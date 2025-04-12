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

    virtual void on_enter() = 0;
    virtual void on_update() = 0;
    virtual void on_draw() = 0;
    virtual void on_input(const ExMessage& msg) = 0;
    virtual void on_exit() = 0;

protected:
    bool right_button_down = false;

    int msg_x = 0;
    int msg_y = 0;
    int index_x = 0;
    int index_y = 0;

    int base_width = 50;
    int row = 10;
    int col = 10;

};