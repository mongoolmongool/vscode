#include "Team.hpp"
#include "Position.hpp"

Team::Team(int team_number, int num_of_pieces, std::vector<const char*> team_imgs) {
    this->team_number = team_number;

    team_images = team_imgs;

    for(int i = 0; i < num_of_pieces; i++) { // 아래 team_images[0]은 후에 일반적인 경우로 수정되어야함.
        current_pieces.push_back(new Piece(team_number, i+1, team_images[i])); // Piece 각각의 개성을 드러내는 건 own_number "i"
    }
}

void Team::initialize() {
    for(auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
        (*it)->initialize();
    }
}

void Team::draw(int num_of_teams) {

    float centerX = -boundaryX + WINDOW_HEIGHT / 12; // 계산 결과에 따른 것
    float centerY = boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * team_number; // 계산 결과에 따른 것

    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(centerX - 20.f / 2.0f, centerY + 20.f / 2.0f);
	glVertex2f(centerX + 20.f / 2.0f, centerY + 20.f / 2.0f);
	glVertex2f(centerX + 20.f / 2.0f, centerY - 20.f / 2.0f);
	glVertex2f(centerX - 20.f / 2.0f, centerY - 20.f / 2.0f);
    glEnd();

    glPopMatrix();

    for (auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
        (*it)->draw(num_of_teams);
    }

}

std::list<Piece*>& Team::get_current_pieces() {
    return current_pieces;
}

void Team::give_a_piece_to_position(Position* destination) {
    // this->current_pieces.back()->piece_type = Piece::PIECE_TYPE::ON_GOING;
    this->current_pieces.back()->get_current_position() = destination;
    destination->get_current_pieces().push_back(this->current_pieces.back());
    this->current_pieces.pop_back();
}

Team::~Team() {
    for(auto it = current_pieces.begin(); it != current_pieces.end(); it++) {
        delete (*it);
    }
}