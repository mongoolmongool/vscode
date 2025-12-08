#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <GL/freeglut.h>
#include "Constants.hpp"
#include "Yoot.hpp"
#include "Map.hpp"
#include "Texture.hpp"

class In_game {
public :
    enum IN_GAME_STATUS { BEFORE_ROLL, PREPARED_TO_ROLL, SELECTING_PIECE, SELECTING_POSITION, PIECE_MOVING };
    // PIECE_MOVING을 마지막 처리의 느낌으로 바꾸어줄 필요가 있음..
    In_game(int num_of_teams, int num_of_pieces);
    ~In_game();

    void play(int current_team_number);
    Position* search_selected_position(float x, float y);
    std::unordered_map<Position*, int> possible_targets(Position* from, std::vector<int> steps);
    Position* decide_the_real_target(std::vector<Position*> targets, float x, float y);

    int how_many_in_tail(int team_number);

    bool is_team_region(float x, float y);
    bool is_position_region(float x, float y);
    bool is_possible_target_region(std::vector<Position*> targets, float x, float y);

    void initialize();
    void idle();
    void display();

    void mouse(int button, int state, int x, int y);
    void keyboardDown(unsigned char key, int x, int y);

    IN_GAME_STATUS in_game_status;

private : 
    int num_of_teams;
    int num_of_pieces;

    int current_team_number;
    // int steps_to_go;
    std::vector<int> steps_to_go;

    //
    int current_step;
    //

    Piece* piece_to_move;
    Yoots* yoots;
    Map* map;
    std::vector<Team*> teams;

    const char* team1_1 = "img/team1/1.png";
    const char* team1_2 = "img/team1/2.png";
    const char* team1_3 = "img/team1/3.png";
    const char* team1_4 = "img/team1/4.png";

    const char* team2_1 = "img/team2/1.png";
    const char* team2_2 = "img/team2/2.png";
    const char* team2_3 = "img/team2/3.png";
    const char* team2_4 = "img/team2/4.png";

    const char* team3_1 = "img/team3/1.png";
    const char* team3_2 = "img/team3/2.png";
    const char* team3_3 = "img/team3/3.png";
    const char* team3_4 = "img/team3/4.png";

    std::vector<std::vector<const char*>> all_images;
};