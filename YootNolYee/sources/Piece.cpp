#include "Piece.hpp"
#include "Position.hpp"

Piece::Piece(int team_num, int own_num, const char* piece_img) {
    team_number = team_num;
    own_number = own_num;
    piece_type = PIECE_TYPE::INITIAL;
    piece_image = piece_img;
    // texture.initializeTexture(piece_img);
}

void Piece::initialize() {
    texture.initializeTexture(piece_image);
}

Piece::~Piece() {
    current_position = nullptr;
}

int Piece::get_team_number() {
    return team_number;
}
    
int Piece::get_own_number() {
    return own_number;
}

Position*& Piece::get_current_position() {
    return current_position;
}

Position*& Piece::get_previous_position() {
    return previous_position;
}

void Piece::draw(int num_of_teams) {
    float centerX = -boundaryX + WINDOW_HEIGHT / 12 * (own_number + 1); // 계산 결과에 따른 것
    float centerY = boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * team_number;

    glPushMatrix();
    texture.draw_texture(centerX, centerY, 30.f, 30.f);
    glPopMatrix();
}

void Piece::draw() {
    float centerX = (*current_position)[0];
    float centerY = (*current_position)[1];

    switch(own_number) {
        case 1 : 
            texture.draw_texture(centerX, centerY, 30.f, 30.f);
            break;
        
        case 2 :
            texture.draw_texture(centerX + get_current_position()->get_size() / 2, centerY + get_current_position()->get_size() / 2, 30.f, 30.f);
            break;
        
        case 3 :
            texture.draw_texture(centerX - get_current_position()->get_size() / 2, centerY - get_current_position()->get_size() / 2, 30.f, 30.f);
            break;

        case 4 : 
            texture.draw_texture(centerX + get_current_position()->get_size() / 2, centerY - get_current_position()->get_size() / 2, 30.f, 30.f);
            break;         
    }

}

// tail에 쓰는 용도
void Piece::draw(float x, float y) {
    texture.draw_texture(x, y, 30.f, 30.f);
}

const char*& Piece::get_piece_image() {
    return piece_image;
}