#pragma once
#include"game_scene.h"
#include"player.h"

extern SceneManager scene_manager;
extern Scene* menu_scene;

extern Player* current_player;
extern Player P1;
extern Player P2;
extern Player Computer;



class LocalPvpScene :public GameScene
{
public:
    void on_enter()
    {
        initgraph(1050,550);
        setbkcolor(RGB(128, 128, 128));
    }

    void on_update()
    {
        if (right_button_down)
        {
            cout << "right_button_down" << endl;
            right_button_down = false;
            index_x = (msg_x / base_width);
            index_y = (msg_y / base_width);

            if (index_x >= 0 && index_x < row && index_y>=0 && index_y < col)
            {
                cout << "in if" << endl;

                if (get_next_player().board.check_board(index_x, index_y))
                {
                    cout << "in if2" << endl;
                    switch_to_next_player();
                    current_player->board.update_board(index_x, index_y);
                }
                cout << "out if" << endl;

            }
        }
        if(!current_player->board.get_ship_count_index())
            scene_manager.switch_to(SceneManager::SceneType::Menu);
    }

    void on_draw()
    {
        current_player->board.draw_player_board_enemy_turn();
        get_next_player().board.draw_player_board();
        draw_tip_text();
    }

    void on_input(const ExMessage& msg)
    {
        msg_x = msg.x;
        msg_y = msg.y;
        if (msg.message == WM_LBUTTONDOWN)
        {
            right_button_down = true;
        }
    }

    void on_exit()
    {

    }

private:
    void draw_tip_text()
    {
        static TCHAR str1[32];
        static TCHAR str2[32];

        if (current_player == &P1)
        {
            _stprintf_s(str1, _T("Player 1 turn"));
            _stprintf_s(str2, _T("Player 1 board"));
        }
        else
        {
            _stprintf_s(str1, _T("Player 2 turn"));
            _stprintf_s(str2, _T("Player 2 board"));
        }

        settextcolor(RGB(0, 0, 0));
        outtextxy(20, 520, str1);
        outtextxy(540, 520, str2);
    }

    Player get_next_player()
    {
        return current_player == &P1 ? P2 : P1;
    }

    void switch_to_next_player()
    {
        current_player == &P1 ? current_player = &P2 : current_player = &P1;
    }

private:

    bool right_button_down = false;

    int msg_x = 0;
    int msg_y = 0;
    int index_x = 0;
    int index_y = 0;

    int base_width = 50;
    int row = 10;
    int col = 10;
};
