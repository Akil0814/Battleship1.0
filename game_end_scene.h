#pragma once
#pragma once
#include"game_scene.h"
#include"player.h"

extern SceneManager scene_manager;
extern Scene* menu_scene;

extern Player* player1;
extern Player* player2;


class GameEndScene :public GameScene
{
public:
    void on_enter()
    {
        initgraph(1050, 550);
        setbkcolor(RGB(128, 128, 128));
    }

    void on_update()
    {
        if (right_button_down)
        {
            scene_manager.switch_to(SceneManager::SceneType::Menu);
            right_button_down = false;
        }
    }

    void on_draw()
    {
        player1->draw_all_ship(true);
        player2->draw_all_ship(false);
        player1->draw_player_board(true, false);
        player2->draw_player_board(false,false);
        draw_tip_text();
    }

    void on_input(const ExMessage& msg)
    {
        if (msg.message == WM_LBUTTONDOWN)
        {
            right_button_down = true;
        }
    }

    void on_exit()
    {
        delete player2;
    }

private:
    void draw_tip_text()
    {
        static TCHAR str1[32];
        static TCHAR str2[32];

        _stprintf_s(str1, _T("Player 1 board"));
        if(HumanPlayer* human = dynamic_cast<HumanPlayer*>(player2))
            _stprintf_s(str2, _T("Player 2 board"));
        else
            _stprintf_s(str2, _T("Computers board"));
        settextcolor(RGB(0, 0, 0));
        outtextxy(20, 520, str1);
        outtextxy(540, 520, str2);
    }
};
