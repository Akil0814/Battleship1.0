#pragma once
#include"game_scene.h"
#include"player.h"
#include"human_player.h"

extern SceneManager scene_manager;
extern Scene* menu_scene;

extern Player* player1;
extern Player* player2;


class LocalPvpScene :public GameScene
{
public:
    void on_enter()
    {
        initgraph(1050,550);
        setbkcolor(RGB(128, 128, 128));
        current_human_player = dynamic_cast<HumanPlayer*>(player1);
    }

    void on_update()
    {
        if (right_button_down)
        {
            right_button_down = false;
            index_x = (msg_x / base_width);
            index_y = (msg_y / base_width);

            if (index_x >= 0 && index_x < row && index_y>=0 && index_y < col)
            {
                if (get_next_player()->check_pos_can_hit(index_x, index_y))
                {
                    switch_to_next_player();
                }
            }
        }
        if(!current_human_player->get_ship_count_index_on_board())
            scene_manager.switch_to(SceneManager::SceneType::Menu);
    }

    void on_draw()
    {
        current_human_player->draw_player_board(false);
        get_next_player()->draw_player_board();
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

        if (current_human_player == player1)
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

    HumanPlayer* get_next_player()
    {
        return current_human_player == player1 ? dynamic_cast<HumanPlayer*>(player2) : dynamic_cast<HumanPlayer*>(player1);
    }

    void switch_to_next_player()
    {
        current_human_player == player1 ? current_human_player = dynamic_cast<HumanPlayer*>(player2) : current_human_player = dynamic_cast<HumanPlayer*>(player1);
    }

private:

    HumanPlayer* current_human_player = nullptr;
};
