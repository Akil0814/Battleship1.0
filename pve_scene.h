#pragma once
#include"game_scene.h"

class PveScene :public GameScene
{
public:
    void on_enter()
    {
        initgraph(1050, 550);
        setbkcolor(RGB(128, 128, 128));
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

};