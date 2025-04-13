#pragma once
#include"game_scene.h"
#include"player.h"
#include"computer_player.h"

extern SceneManager scene_manager;
extern Scene* game_end_scene;

extern Player* player1;
extern Player* player2;

class PveScene :public GameScene
{
public:
    void on_enter()
    {
        initgraph(1050, 550);
        setbkcolor(RGB(128, 128, 128));
        human_player = dynamic_cast<HumanPlayer*>(player1);
        computer_player = dynamic_cast<ComputerPlayer*>(player2);
    }
    void on_update()
    {
        if (right_button_down)
        {
            right_button_down = false;
            index_x = (msg_x / base_width);
            index_y = (msg_y / base_width);

            if (index_x >= 0 && index_x < row && index_y >= 0 && index_y < col)
            {
                if (computer_player->check_pos_can_hit(index_x, index_y))
                {
                    POINT try_hit;
                    do
                    {
                        try_hit = computer_player->decide_attack_position();
                    } while (!human_player->check_board_available(try_hit.x, try_hit.y));
                    computer_player->check_if_hit_target(human_player->check_pos_type(try_hit.x, try_hit.y));
                    human_player->update_board(try_hit.x, try_hit.y);
                }
            }
        }
        if (!computer_player->get_ship_count_index_on_board()|| !human_player->get_ship_count_index_on_board())
            scene_manager.switch_to(SceneManager::SceneType::Game_end);
    }

    void on_draw()
    {
        human_player->draw_player_board(false);
        computer_player->draw_player_board(true);
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
        delete this;
    }
private:
    void draw_tip_text()
    {
        static TCHAR str1[32];
        static TCHAR str2[32];

        _stprintf_s(str1, _T("Players board"));
        _stprintf_s(str2, _T("Computers board"));
        settextcolor(RGB(0, 0, 0));
        outtextxy(540, 520, str1);
        outtextxy(20, 520, str2);
    }

private:
    HumanPlayer* human_player = nullptr;
    ComputerPlayer* computer_player = nullptr;
};