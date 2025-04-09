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

private:
    // ͨ����ϷԪ��
    //Board playerBoard;
    //Board enemyBoard;
    int currentTurn;
    // ... �Ž�ͧ���ж���Ӯ��ͨ���߼�
};