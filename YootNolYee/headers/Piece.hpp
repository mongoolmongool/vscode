#pragma once

#include "Constants.hpp"
#include "Texture.hpp"
#include <GL/freeglut.h>

class Position;

class Piece { // 아마 얘가 사진도 들고 있어야 할듯?
public :
    enum PIECE_TYPE { INITIAL, ON_GOING, ARRIVED };

    Piece(int team_number, int own_number, const char* piece_img);
    ~Piece();
    int get_team_number();
    int get_own_number();
    Position*& get_current_position();
    Position*& get_previous_position();
    PIECE_TYPE piece_type;

    void draw(int num_of_teams);
    void draw();
    void draw(float x, float y);
    void initialize();

    const char*& get_piece_image();

private :   
    int team_number;
    int own_number;

    Position* current_position;
    Position* previous_position;

    const char* piece_image;

    Texture texture;
};