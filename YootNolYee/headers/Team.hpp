#pragma once

#include <list>
#include <vector>
#include <GL/freeglut.h>
#include "Piece.hpp"
#include "Constants.hpp"

class Position; // 전방 선언 --> circular inclusion을 막기 위함임.

class Team {
public :
    Team(int team_number, int num_of_pieces, std::vector<const char*> team_imgs);
    ~Team();

    std::list<Piece*>& get_current_pieces();

    void give_a_piece_to_position(Position* destination); // 처음 출발하는 경우

    void draw(int num_of_teams);
    void initialize();

private :
    std::list<Piece*> current_pieces;
    int team_number;

    std::vector<const char*> team_images;
};