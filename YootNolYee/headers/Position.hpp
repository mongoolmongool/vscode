#pragma once

#include <vector>
#include <list>
#include <tuple>

#include "Piece.hpp"
#include "Team.hpp"
#include <iostream>
#include <GL/freeglut.h>

class Position {
public :
    enum POS_TYPE { SENTINEL, ONE_WAY, TWO_WAY, TAIL };

    Position(float x, float y, POS_TYPE type);
    ~Position();

    void set_center(float x, float y);
    float& get_center();
    float& operator[](const int i);

    std::vector<Position*>& get_prevs();
    std::vector<Position*>& get_nexts();

    std::list<Piece*>& get_current_pieces();

    float get_size();

    Position* search(float x, float y);

    void toss_a_piece(Position* destination); // Position에서 Position으로
    void give_pieces_to_team(Team* destination); // 다른 팀에 의해 먹힌 경우
                                                 // 그냥 갖고 있는 piece의 team_number를 알아내서 push_back 해주면 됨.
    

    void draw(); // OPENGL

    bool Is_deleted();

    POS_TYPE pos_type;

private :
    float center[2];
    float color[3];
    float size;

    bool deleted;

    std::vector<Position*> prevs;
    std::vector<Position*> nexts;

    std::list<Piece*> current_pieces;
};

void make_relationship(Position* prev, Position* next);