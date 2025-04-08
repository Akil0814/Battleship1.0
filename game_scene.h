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

    virtual void on_enter();
    virtual void on_update();
    virtual void on_draw();
    virtual void on_input(const ExMessage& msg);
    virtual void on_exit();

private:
    // 通用游戏元素
    //Board playerBoard;
    //Board enemyBoard;
    int currentTurn;
    // ... 放舰艇、判断输赢等通用逻辑

};